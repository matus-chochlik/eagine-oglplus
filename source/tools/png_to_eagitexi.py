#!/usr/bin/env python3
# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt

import os
import sys
import argparse

# ------------------------------------------------------------------------------
class ArgumentParser(argparse.ArgumentParser):
    # -------------------------------------------------------------------------
    def __init__(self, **kw):
        def _natural_int(x):
            try:
                assert(int(x) > 0)
                return int(x)
            except:
                self.error("`%s' is not a positive integer value" % str(x))

        argparse.ArgumentParser.__init__(self, **kw)

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

        self.add_argument(
            "--level", "-l",
            metavar='INTEGER',
            dest='image_level',
            nargs='?',
            type=_natural_int,
            default=0
        )

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

        return _Options(self.processParsedOptions(
            argparse.ArgumentParser.parse_args(self)
        ))

# ------------------------------------------------------------------------------
def getArgumentParser():
    return ArgumentParser(
        prog=os.path.basename(__file__),
        description="""
            Converts a PNG image into eagitex texture image file.
        """
    )
# ------------------------------------------------------------------------------
class PngImage(object):
    # -------------------------------------------------------------------------
    def __init__(self, input_path):
        self._png_image = None
        self._pil_image = None
        try:
            import PIL.Image
            self._pil_image = PIL.Image.open(input_path)
        except: pass

        assert self._png_image or self._pil_image

    # -------------------------------------------------------------------------
    def width(self):
        if self._pil_image:
            return self._pil_image.width

    # -------------------------------------------------------------------------
    def height(self):
        if self._pil_image:
            return self._pil_image.height

    # -------------------------------------------------------------------------
    def has_alpha(self):
        if self._pil_image:
            for e in self._pil_image.getdata(band=3):
                if e != 255:
                    return True
            return False

    # -------------------------------------------------------------------------
    def channels(self):
        if self._pil_image:
            if self._pil_image.mode == "RGBA":
                return 4 if self.has_alpha() else 3
            if self._pil_image.mode == "RGB":
                return 3
            if self._pil_image.mode == "1":
                return 1
            if self._pil_image.mode == "L":
                return 1

    # -------------------------------------------------------------------------
    def data_type(self):
        if self._pil_image:
            return "unsigned_byte"

    # -------------------------------------------------------------------------
    def format(self):
        if self._pil_image:
            if self._pil_image.mode == "RGBA":
                return "rgba" if self.has_alpha() else "rgb"
            if self._pil_image.mode == "RGB":
                return "rgb"
            if self._pil_image.mode == "1":
                return "red"
            if self._pil_image.mode == "L":
                return "red"

    # -------------------------------------------------------------------------
    def iformat(self):
        if self._pil_image:
            if self._pil_image.mode == "RGBA":
                return "rgba8" if self.has_alpha() else "rgb8"
            if self._pil_image.mode == "RGB":
                return "rgb8"
            if self._pil_image.mode == "1":
                return "r8"
            if self._pil_image.mode == "L":
                return "r8"

    # -------------------------------------------------------------------------
    def same_format_as(self, that):
        return (self.data_type() == that.data_type()) and\
            (self.channels() == that.channels()) and\
            (self.iformat() == that.iformat())

    # -------------------------------------------------------------------------
    def elements(self):
        if self._pil_image:
            nc = self.channels()
            for e in self._pil_image.getdata():
                for c in range(nc):
                    yield e[c]

    # -------------------------------------------------------------------------
    def data_filter(self, options):
        if options.gzip_data:
            try:
                import zlib
                return "zlib"
            except:
                pass
        return "none"

    # -------------------------------------------------------------------------
    def chunks(self):
        if self._pil_image:
            nc = self.channels()
            temp = bytearray()
            for e in self._pil_image.getdata():
                for c in range(nc):
                    temp += e[c].to_bytes(1, "little")
                if len(temp) >= 4096:
                    yield temp
                    temp = bytearray()
            yield temp

# ------------------------------------------------------------------------------
def convert(options):
    image0 = PngImage(options.input_paths[0])
    options.write('{"level":%d\n' % options.image_level)
    options.write(',"width":%d\n' % image0.width())
    options.write(',"height":%d\n' % image0.height())
    if(len(options.input_paths) > 1):
        options.write(',"depth":%d\n' % len(options.input_paths))
    options.write(',"channels":%d\n' % image0.channels())
    options.write(',"data_type":"%s"\n' % image0.data_type())
    options.write(',"format":"%s"\n' % image0.format())
    options.write(',"iformat":"%s"\n' % image0.iformat())

    def _images(image0, options):
        yield image0
        for input_path in options.input_paths[1:]:
            image = PngImage(input_path)
            assert image.same_format_as(image0)
            yield image

    if options.write_elements:
        options.write(',"data":[')
        first_element = True
        for img in _images(image0, options):
            for e in img.elements():
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
            zobj = zlib.compressobj(9)
            for img in _images(image0, options):
                for chunk in img.chunks():
                    compressed = zobj.compress(chunk)
                    if compressed:
                        options.write(compressed)
                compressed = zobj.compress(chunk)
                if compressed:
                    options.write(compressed)
        except:
            for img in _images(image0, options):
                for chunk in img.chunks():
                    options.write(chunk)

# ------------------------------------------------------------------------------
def main():
    try:
        options = getArgumentParser().parseArgs()
        convert(options)
        return 0
    except Exception as error:
        print(error)
        try: os.remove(options.output_path)
        except: pass
        return 1

# ------------------------------------------------------------------------------
if __name__ == '__main__':
    sys.exit(main())
