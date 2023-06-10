#!/usr/bin/env python3
# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt

import os
import sys
import argparse
import shutil
import subprocess
import tempfile

# ------------------------------------------------------------------------------
class PngInputs(object):
    # -------------------------------------------------------------------------
    def _convert_svg2png(self, input_path):
        output_path = os.path.basename(input_path)+'.png'
        output_path = os.path.join(self._work_dir, output_path)
        cmdline = [
            self._options.inkscape_command,
            '--batch-process',
            '--export-overwrite',
            '--export-area-page',
            '--export-filename=%s' % output_path,
            input_path]
        subprocess.run(cmdline)
        return output_path

    # -------------------------------------------------------------------------
    def _convert(self, input_path):
        ext = os.path.splitext(input_path)[-1]
        if ext == ".svg":
            return self._convert_svg2png(input_path)
    # -------------------------------------------------------------------------
    def __init__(self, options):
        self._options = options
        self._work_dir = tempfile.mkdtemp()
        self._converted_inputs = [self._convert(p) for p in options.input_paths]

    # -------------------------------------------------------------------------
    def __del__(self):
        shutil.rmtree(self._work_dir)

    # -------------------------------------------------------------------------
    def __len__(self):
        return len(self._converted_inputs)

    # -------------------------------------------------------------------------
    def __getitem__(self, index):
        assert isinstance(index, slice) or isinstance(index, int)
        return self._converted_inputs[index]

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
            "--inkscape",
            metavar='PATH',
            dest='inkscape_command',
            nargs='?',
            default='inkscape'
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
            type=_positive_int,
            default=0
        )

        self.add_argument(
            "--x-offs", "-X",
            metavar='INTEGER',
            dest='x_offs',
            nargs='?',
            type=_positive_int,
            default=0
        )

        self.add_argument(
            "--y-offs", "-Y",
            metavar='INTEGER',
            dest='y_offs',
            nargs='?',
            type=_positive_int,
            default=0
        )

        self.add_argument(
            "--z-offs", "-Z",
            metavar='INTEGER',
            dest='z_offs',
            nargs='?',
            type=_positive_int,
            default=0
        )

        self.add_argument(
            "--eagitex",
            dest='eagitex',
            action='store_true',
            default=False
        )

        self.add_argument(
            "--flip-y",
            dest='flip_y',
            action='store_true',
            default=False
        )

        self.add_argument(
            "--cube-map",
            dest='cube_map',
            action='store_true',
            default=False
        )

        self.add_argument(
            "--tex-param", "-P",
            metavar=('NAME', 'VALUE'),
            dest='texture_parameters',
            nargs=2,
            action='append',
            default=[]
        )

    # -------------------------------------------------------------------------
    def processParsedOptions(self, options):
        if options.cube_map:
            options.flip_y = True
            if len(options.input_paths) % 6 != 0:
                raise argparse.ArgumentTypeError("invalid number of cube-map images")

        options.input_paths = PngInputs(options)

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
            Converts a PNG image into eagitexi texture image file.
        """
    )
# ------------------------------------------------------------------------------
# PILPngImageAdapter
# ------------------------------------------------------------------------------
class PILPngImageAdapter(object):
    # -------------------------------------------------------------------------
    def __init__(self, img):
        self._img = img
        self._has_palette = False
        self._data_type = "unsigned_byte"

        has_transparency = "transparency" in self._img.info
        has_alpha = False
        try:
            for e in self._img.getdata(band=3):
                if e != 255:
                    has_alpha = True
                    break
        except:
            pass

        mode = self._img.mode

        if mode == "RGBA":
            self._channels = 4 if has_alpha else 3
            self._format = "rgba" if has_alpha else "rgb"
            self._iformat = "rgba8" if has_alpha else "rgb8"
        if mode == "RGB":
            self._channels = 3
            self._format = "rgb"
            self._iformat = "rgb8"
        if mode in ["L", "1"]:
            self._channels = 1
            self._format = "red"
            self._iformat = "r8"
        if mode == "P":
            self._has_palette = True
            pmode = self._img.palette.mode
            if pmode in["RGBA", "RGB"]:
                self._channels = 4 if has_transparency else 3
                self._format = "rgba" if has_transparency else "rgb"
                self._iformat = "rgba8" if has_transparency else "rgb8"
            if pmode in ["L", "1"]:
                self._channels = 1
                self._format = "red"
                self._iformat = "r8"

    # -------------------------------------------------------------------------
    def width(self):
        return self._img.width

    # -------------------------------------------------------------------------
    def height(self):
        return self._img.height

    # -------------------------------------------------------------------------
    def channels(self):
        return self._channels

    # -------------------------------------------------------------------------
    def data_type(self):
        return self._data_type

    # -------------------------------------------------------------------------
    def format(self):
        return self._format

    # -------------------------------------------------------------------------
    def iformat(self):
        return self._iformat

    # -------------------------------------------------------------------------
    def chunks(self):
        nc = self.channels()
        chunk_size = 64 * 1024
        mode = self._img.mode
        temp = bytearray()
        if mode == "P":
            p = {i:c for c,i in self._img.palette.colors.items()}
            prev = p[0]
            for i in range(256):
                try:
                    prev = p[i]
                except KeyError:
                    p[i] = prev

            transparency = self._img.info.get("transparency")
            if transparency:
                for i, a in zip(range(len(transparency)), transparency):
                    r,g,b = p[i]
                    p[i] = (r,g,b,a)

            for i in self._img.getdata():
                e = p[i]
                for c in range(nc):
                    temp += bytes([e[c]])
                if len(temp) >= chunk_size:
                    yield temp
                    temp = bytearray()
            yield temp
        elif mode in ["L", "1"]:
            for e in self._img.getdata():
                temp += bytes([e])
                if len(temp) >= chunk_size:
                    yield temp
                    temp = bytearray()
            yield temp
        else:
            for e in self._img.getdata():
                for c in range(nc):
                    temp += bytes([e[c]])
                if len(temp) >= chunk_size:
                    yield temp
                    temp = bytearray()
            yield temp

# ------------------------------------------------------------------------------
class PngImage(object):
    # -------------------------------------------------------------------------
    def __init__(self, options, input_path):
        self._delegate = None
        try:
            import PIL.Image
            png = PIL.Image.open(input_path)
            if not options.flip_y: # Yes, not
                png.transpose(PIL.Image.FLIP_TOP_BOTTOM)
            self._delegate = PILPngImageAdapter(png)
        except: raise

        assert self._delegate is not None

    # -------------------------------------------------------------------------
    def width(self):
        return self._delegate.width()

    # -------------------------------------------------------------------------
    def height(self):
        return self._delegate.height()

    # -------------------------------------------------------------------------
    def channels(self):
        return self._delegate.channels()

    # -------------------------------------------------------------------------
    def data_type(self):
        return self._delegate.data_type()

    # -------------------------------------------------------------------------
    def format(self):
        return self._delegate.format()

    # -------------------------------------------------------------------------
    def iformat(self):
        return self._delegate.iformat()

    # -------------------------------------------------------------------------
    def same_format_as(self, that):
        return (self.data_type() == that.data_type()) and\
            (self.channels() == that.channels()) and\
            (self.iformat() == that.iformat())

    # -------------------------------------------------------------------------
    def elements(self):
        return self._delegate.elements()

    # -------------------------------------------------------------------------
    def chunks(self):
        return self._delegate.chunks()

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
    image0 = PngImage(options, options.input_paths[0])
    if options.eagitex:
        options.write('{"levels":1\n')
    else:
        options.write('{"level":%d\n' % options.image_level)
    if options.x_offs > 0:
        options.write(',"x_offs":%d\n' % options.x_offs)
    if options.y_offs > 0:
        options.write(',"y_offs":%d\n' % options.y_offs)
    if options.z_offs > 0:
        options.write(',"z_offs":%d\n' % options.z_offs)
    options.write(',"width":%d\n' % image0.width())
    options.write(',"height":%d\n' % image0.height())
    if(len(options.input_paths) > 1):
        options.write(',"depth":%d\n' % len(options.input_paths))
    options.write(',"channels":%d\n' % image0.channels())
    options.write(',"data_type":"%s"\n' % image0.data_type())
    options.write(',"format":"%s"\n' % image0.format())
    options.write(',"iformat":"%s"\n' % image0.iformat())

    for name, value in options.texture_parameters:
        try:
            options.write(',"%s":%d\n' % (name, int(value)))
        except ValueError:
            try:
                options.write(',"%s":%f\n' % (name, float(value)))
            except ValueError:
                options.write(',"%s":"%s"\n' % (name, value))

    def _images(image0, options):
        yield image0
        for input_path in options.input_paths[1:]:
            image = PngImage(options, input_path)
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
            zobj = zlib.compressobj(zlib.Z_BEST_COMPRESSION)
            for img in _images(image0, options):
                for chunk in img.chunks():
                    compressed = zobj.compress(chunk)
                    if compressed:
                        options.write(compressed)
            compressed = zobj.flush()
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
        print(type(error), error)
        try: os.remove(options.output_path)
        except: pass
        raise
        return 1

# ------------------------------------------------------------------------------
if __name__ == '__main__':
    sys.exit(main())
