#!/usr/bin/env python3
# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt

import os
import sys
import argparse

# ------------------------------------------------------------------------------
#  Generators
# ------------------------------------------------------------------------------
def argPositiveInt(x):
    try:
        assert(int(x) > 0)
        return int(x)
    except:
        self.error("`%s' is not a positive integer value" % str(x))
# ------------------------------------------------------------------------------
class ImageGenerator(object):
    # -------------------------------------------------------------------------
    def __init__(self, options):
        self._options = options

    # -------------------------------------------------------------------------
    @staticmethod
    def addArguments(argparser):

        argparser.add_argument(
            "--elements", "-E",
            dest='write_elements',
            action="store_true",
            default=False
        )

        argparser.add_argument(
            "--gzip", "-z",
            dest='gzip_data',
            action="store_true",
            default=False
        )

        argparser.add_argument(
            "--width", "-W",
            dest='width',
            action="store",
            type=argPositiveInt,
            default=512
        )

        argparser.add_argument(
            "--height", "-H",
            dest='height',
            action="store",
            type=argPositiveInt,
            default=512
        )

    # -------------------------------------------------------------------------
    def level(self):
        return 0

    # -------------------------------------------------------------------------
    def width(self):
        return self._options.width

    # -------------------------------------------------------------------------
    def height(self):
        return self._options.height

    # -------------------------------------------------------------------------
    def elements(self):
        for z in range(self.depth()):
            for y in range(self.height()):
                for x in range(self.width()):
                    yield self.element_value(x, y, z)

    # -------------------------------------------------------------------------
    def chunks(self):
        for z in range(self.depth()):
            for y in range(self.height()):
                yield bytes([self.element_value(x, y, z) for x in range(self.width())])

    # -------------------------------------------------------------------------
    def data_filter(self):
        if self._options.gzip_data:
            try:
                import zlib
                return "zlib"
            except:
                pass
        return "none"

# ------------------------------------------------------------------------------
#  Checker
# ------------------------------------------------------------------------------
class CheckerImage(ImageGenerator):
    # -------------------------------------------------------------------------
    def __init__(self, options):
        ImageGenerator.__init__(self, options)
        self._cell_px = options.width / options.divisions

    # -------------------------------------------------------------------------
    @staticmethod
    def addArguments(argparser):
        ImageGenerator.addArguments(argparser)

        grp = argparser.add_argument_group()
        grp.add_argument(
            "--checker",
            dest='generator',
            action="store_const",
            const="checker"
        )
        grp.add_argument(
            "--divisions",
            action="store",
            type=argPositiveInt,
            default=16
        )

    # -------------------------------------------------------------------------
    def depth(self):
        return 1

    # -------------------------------------------------------------------------
    def channels(self):
        return 1

    # -------------------------------------------------------------------------
    def data_type(self):
        return "unsigned_byte"

    # -------------------------------------------------------------------------
    def format(self):
        return "red"

    # -------------------------------------------------------------------------
    def iformat(self):
        return "r8"

    # -------------------------------------------------------------------------
    def _cell(self, x, y):
        return (x // self._cell_px) % 2 == (y // self._cell_px) % 2

    # -------------------------------------------------------------------------
    def element_value(self, x, y, z):
            return 0xA0 if self._cell(x, y) else 0x60

# ------------------------------------------------------------------------------
def makeGenerator(options):
    # TODO
    return CheckerImage(options)

# ------------------------------------------------------------------------------
#  Argument parsing
# ------------------------------------------------------------------------------
class ArgumentParser(argparse.ArgumentParser):
    # -------------------------------------------------------------------------
    def __init__(self, **kw):
        argparse.ArgumentParser.__init__(self, **kw)

        self.add_argument(
            "--output", "-o",
            metavar='OUTPUT-FILE',
            dest='output_path',
            nargs='?',
            type=os.path.realpath,
            default=None
        )

        CheckerImage.addArguments(self)

    # -------------------------------------------------------------------------
    def processParsedOptions(self, options):
        if options.output_path is None:
            options.output = sys.stdout
        else:
            options.output = open(options.output_path, "w")
        return options

    # -------------------------------------------------------------------------
    def parseArgs(self):
        # ----------------------------------------------------------------------
        class _Options(object):
            # ------------------------------------------------------------------
            def __init__(self, base):
                self.__dict__.update(base.__dict__)
            # ------------------------------------------------------------------
            def write(self, data):
                if type(data) is str:
                    self.output.buffer.write(data.encode("utf8"))
                else:
                    self.output.buffer.write(data)
        # ----------------------------------------------------------------------
        return _Options(self.processParsedOptions(
            argparse.ArgumentParser.parse_args(self)
        ))

# ------------------------------------------------------------------------------
def getArgumentParser():
    return ArgumentParser(
        prog=os.path.basename(__file__),
        description="""
            Generates eagitexi texture image file.
        """
    )
# ------------------------------------------------------------------------------
#  Generate texture
# ------------------------------------------------------------------------------
def generate(options):
    generator = makeGenerator(options)
    options.write('{"level":%d\n' % generator.level())
    options.write(',"width":%d\n' % generator.width())
    options.write(',"height":%d\n' % generator.height())
    options.write(',"depth":%d\n' % generator.depth())
    options.write(',"channels":%d\n' % generator.channels())
    options.write(',"data_type":"%s"\n' % generator.data_type())
    options.write(',"format":"%s"\n' % generator.format())
    options.write(',"iformat":"%s"\n' % generator.iformat())

    if options.write_elements:
        options.write(',"data":[')
        first_element = True
        for e in generator.elements():
            if first_element:
                first_element = False
            else:
                options.write(",")
            options.write("%d" % e)
        options.write(']')
    else:
        options.write(',"data_filter":"%s"' % generator.data_filter())
    options.write('}')
    if not options.write_elements:
        try:
            assert options.gzip_data
            import zlib
            zobj = zlib.compressobj(zlib.Z_BEST_COMPRESSION)
            for chunk in generator.chunks():
                compressed = zobj.compress(chunk)
                if compressed:
                    options.write(compressed)
            compressed = zobj.flush()
            if compressed:
                options.write(compressed)
        except:
            for chunk in generator.chunks():
                options.write(chunk)

# ------------------------------------------------------------------------------
#  Main function
# ------------------------------------------------------------------------------
def main():
    try:
        options = getArgumentParser().parseArgs()
        generate(options)
        return 0
    except Exception as error:
        print(type(error), error)
        try: os.remove(options.output_path)
        except: pass
        raise
        return 1

# ------------------------------------------------------------------------------
if __name__ == '__main__':
    sys.exit(main())
