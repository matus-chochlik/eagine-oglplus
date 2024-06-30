#!/usr/bin/env python3
# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# https://www.boost.org/LICENSE_1_0.txt

import os
import sys
import argparse

# ------------------------------------------------------------------------------
class ArgumentParser(argparse.ArgumentParser):
    # -------------------------------------------------------------------------
    def __init__(self, **kw):
        def _positive_int(x):
            try:
                assert(int(x) > 0)
                return int(x)
            except:
                self.error("`%s' is not a positive integer value" % str(x))

        argparse.ArgumentParser.__init__(self, **kw)

        self.add_argument(
            "--print-bash-completion",
            metavar='FILE|-',
            dest='print_bash_completion',
            default=None
        )

        self.add_argument(
            "--rank", "-R",
            metavar='INTEGER',
            dest='tiling_rank',
            nargs='?',
            type=_positive_int,
            default=4
        )

        self.add_argument(
            "--elements", "-E",
            dest='write_elements',
            action="store_true",
            default=False
        )

        self.add_argument(
            "--gzip", "-z",
            dest='gzip_data',
            action="store_true",
            default=False
        )

        self.add_argument(
            "--input", "-i",
            metavar='INPUT-FILE',
            dest='input_paths',
            nargs='?',
            type=os.path.realpath,
            action="append",
            default=[]
        )

        self.add_argument(
            "--output", "-o",
            metavar='OUTPUT-FILE',
            dest='output_path',
            nargs='?',
            type=os.path.realpath,
            default=None
        )

    # -------------------------------------------------------------------------
    def processParsedOptions(self, options):
        # TODO
        assert options.tiling_rank == 4

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

        return _Options(self.processParsedOptions(
            argparse.ArgumentParser.parse_args(self)
        ))

# ------------------------------------------------------------------------------
def getArgumentParser():
    return ArgumentParser(
        prog=os.path.basename(__file__),
        description="""
            Converts a NxN tiling image into eagitexi texture image file.
        """
    )
# ------------------------------------------------------------------------------
class TilingImage(object):
    # -------------------------------------------------------------------------
    def _open(self, input_path):
        if input_path == "-":
            return sys.stdin
        else:
            return open(input_path, "rt")

    # -------------------------------------------------------------------------
    def __init__(self, input_path):
        self._lines = []
        for line in self._open(input_path):
            line = line.strip()
            if line:
                self._lines.append(line)
                assert len(line) == len(self._lines[0])

    # -------------------------------------------------------------------------
    def width(self):
        return len(self._lines[0])

    # -------------------------------------------------------------------------
    def height(self):
        return len(self._lines)

    # -------------------------------------------------------------------------
    def element_value(self, options, e):
        if options.tiling_rank == 4:
            return "0123456789ABCDEF".find(e.upper())

    # -------------------------------------------------------------------------
    def elements(self, options):
        for line in self._lines:
            for e in line:
                yield self.element_value(options, e)

    # -------------------------------------------------------------------------
    def chunks(self, options):
        for line in self._lines:
            yield bytes([self.element_value(options, c) for c in line])

    # -------------------------------------------------------------------------
    def data_filter(self, options):
        if options.gzip_data:
            try:
                import zlib
                return "zlib"
            except:
                pass
        return "none"

# ------------------------------------------------------------------------------
def convert(options):
    image0 = TilingImage(options.input_paths[0])
    options.write('{"level":%d\n' % 0)
    options.write(',"width":%d\n' % image0.width())
    options.write(',"height":%d\n' % image0.height())
    if(len(options.input_paths) > 1):
        options.write(',"depth":%d\n' % len(options.input_paths))
    options.write(',"channels":%d\n' % 1)
    options.write(',"data_type":"%s"\n' % "unsigned_byte")
    options.write(',"format":"%s"\n' % "red_integer")
    options.write(',"iformat":"%s"\n' % "r8ui")

    def _images(image0, options):
        yield image0
        for input_path in options.input_paths[1:]:
            image = TilingImage(input_path)
            yield image

    if options.write_elements:
        options.write(',"data":[')
        first_element = True
        for img in _images(image0, options):
            for e in img.elements(options):
                if first_element:
                    first_element = False
                else:
                    options.write(",")
                options.write("%d" % e)
        options.write(']')
    else:
        options.write(',"data_filter":"%s"' % image0.data_filter(options))
    options.write('}')
    if not options.write_elements:
        try:
            assert options.gzip_data
            import zlib
            zobj = zlib.compressobj(zlib.Z_BEST_COMPRESSION)
            for img in _images(image0, options):
                for chunk in img.chunks(options):
                    compressed = zobj.compress(chunk)
                    if compressed:
                        options.write(compressed)
            compressed = zobj.flush()
            if compressed:
                options.write(compressed)
        except:
            for img in _images(image0, options):
                for chunk in img.chunks(options):
                    options.write(chunk)

# ------------------------------------------------------------------------------
#  bash completion
# ------------------------------------------------------------------------------
def printBashCompletion(argparser, options):
    from eagine.argparseUtil import printBashComplete
    def _printIt(fd):
        printBashComplete(
            argparser,
            "_eagine_tiling_to_eagitexi",
            "eagine-tiling-to-eagitexi",
            ["--print-bash-completion"],
            fd)
    if options.print_bash_completion == "-":
        _printIt(sys.stdout)
    else:
        with open(options.print_bash_completion, "wt") as fd:
            _printIt(fd)

# ------------------------------------------------------------------------------
#  main
# ------------------------------------------------------------------------------
def main():
    try:
        argparser = getArgumentParser()
        options = argparser.parseArgs()
        if options.print_bash_completion:
            printBashCompletion(argparser, options)
            return 0
        else:
            convert(options)
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
