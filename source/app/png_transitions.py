#!/usr/bin/env python3
# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt

import os
import sys
import zlib
import numpy
import random
import argparse

# ------------------------------------------------------------------------------
#  Argument parsing
# ------------------------------------------------------------------------------
class NoVariantGetter(object):
    # -------------------------------------------------------------------------
    def __call__(self, x, y, i):
        return ""

    # -------------------------------------------------------------------------
    def options(self):
        yield ""

# ------------------------------------------------------------------------------
class ConstantVariantGetter(object):
    # -------------------------------------------------------------------------
    def __init__(self, c):
        self._v = str(c)

    # -------------------------------------------------------------------------
    def __call__(self, x, y, i):
        return self._v

    # -------------------------------------------------------------------------
    def options(self):
        return self._v

# ------------------------------------------------------------------------------
class RandomVariantGetter(object):
    # -------------------------------------------------------------------------
    def __init__(self, mn, mx):
        self._choices = [("%X" % x) for x in range(mn, mx+1)]

    # -------------------------------------------------------------------------
    def __call__(self, x, y, i):
        return random.choice(self._choices)

    # -------------------------------------------------------------------------
    def options(self):
        for c in self._choices:
            yield c

# ------------------------------------------------------------------------------
class TilingVariantGetter(object):
    # -------------------------------------------------------------------------
    def __init__(self, fd):
        self._choices = set()
        self._rows = None
        for line in fd:
            line = line.strip();
            for c in line:
                self._choices.add(c)
            if len(line) == 0:
                break
            if self._rows:
                assert len(line) == len(self._rows[0])
                self._rows.append(line)
            else:
                self._rows = [line]
        assert self._rows

    # -------------------------------------------------------------------------
    def __call__(self, x, y, i):
        y = y % len(self._rows)
        x = x % len(self._rows[y])
        return self._rows[y][x]

    # -------------------------------------------------------------------------
    def options(self):
        for c in self._choices:
            yield c

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

        def _variant_kind(x):
            try:
                v = int(x)
                assert v >= 0 or v <= 16
                return ConstantVariantGetter(v)
            except:
                try:
                    return TilingVariantGetter(open(x, "rt"))
                except:
                    if x == "random16":
                        return RandomVariantGetter(0, 15)
                    self.error("`%s' is not a valid variant specifier" % str(x))

        argparse.ArgumentParser.__init__(self, **kw)

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
            "--output-type", "-T",
            metavar='TYPE',
            dest='output_type',
            nargs='?',
            choices=["eagitexi", "eagitex", "ascii", "html", "orig"],
            default="eagitexi"
        )

        self.add_argument(
            "--eagitex",
            dest='eagitex',
            action='store_true',
            default=False
        )

        self.add_argument(
            "--channel", "-c",
            metavar='VALUE',
            dest='channel',
            nargs='?',
            type=_positive_int,
            default=0
        )

        self.add_argument(
            "--threshold", "-t",
            metavar='VALUE',
            dest='threshold',
            nargs='?',
            type=_positive_int,
            default=128
        )

        self.add_argument(
            "--variant", "-V",
            metavar='VALUE',
            dest='variant',
            nargs='?',
            type=_variant_kind,
            default=NoVariantGetter()
        )

        self.add_argument(
            "--name-format", "-N",
            metavar='VALUE',
            dest='name_format',
            nargs='?',
            default="tile_%02X%s.png"
        )

        self.add_argument(
            "--invert", "-I",
            dest='invert',
            action="store_true",
            default=False
        )

        muog = self.add_mutually_exclusive_group()

        muog.add_argument(
            "--print-combinations", "-C",
            dest='print_combinations',
            action="store_true",
            default=False
        )

        muog.add_argument(
            "--print-missing", "-M",
            dest='print_missing',
            action="store_true",
            default=False
        )

    # -------------------------------------------------------------------------
    def processParsedOptions(self, options):
        if options.eagitex and options.output_type == "eagitexi":
            options.output_type = "eagitex"
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
#  Transitions indices
# ------------------------------------------------------------------------------
def pixel_configurations():
    for i in range(512):
        mat = []
        for by in range(3):
            row = []
            for bx in range(3):
                b = 0x01 << (by * 3 + bx)
                row.append(i & b == b)
            mat.append(row)
        yield numpy.array([row for row in mat])
# ------------------------------------------------------------------------------
def make_combinations():
    combinations = set()
    for mat in pixel_configurations():
        combinations.add(transition_code(mat))

    for c in combinations:
        yield c
# ------------------------------------------------------------------------------
_transition_combinations = None
def get_combinations():
    global _transition_combinations
    if _transition_combinations is None:
        _transition_combinations = sorted([c for c in make_combinations()])
    return _transition_combinations
# ------------------------------------------------------------------------------
def transition_index(code):
    return get_combinations().index(code)

# ------------------------------------------------------------------------------
def transition_code(k):
    i = 0x00
    if k[1,1]:
        i = 0xFF
    else:
        if k[1,0]:
            i |= 0x01
        if k[0,1]:
            i |= 0x02
        if k[2,1]:
            i |= 0x04
        if k[1,2]:
            i |= 0x08

        if k[0,0] and not k[1,0] and not k[0,1]:
            i |= 0x10
        if k[2,0] and not k[1,0] and not k[2,1]:
            i |= 0x20
        if k[0,2] and not k[0,1] and not k[1,2]:
            i |= 0x40
        if k[2,2] and not k[2,1] and not k[1,2]:
            i |= 0x80

    return i

# ------------------------------------------------------------------------------
#  PNG loading
# ------------------------------------------------------------------------------
class PILPngImageAdapter(object):
    # -------------------------------------------------------------------------
    def __init__(self, img):
        self._img = img
        self._has_palette = False

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
        if mode == "RGB":
            self._channels = 3
        if mode in ["L", "1"]:
            self._channels = 1
        if mode == "P":
            self._has_palette = True
            pmode = self._img.palette.mode
            if pmode in["RGBA", "RGB"]:
                self._channels = 4 if has_transparency else 3
            if pmode in ["L", "1"]:
                self._channels = 1

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
    def same_format_as(self, that):
        return (self.width() == that.width()) and \
                (self.height() == that.height())

    # -------------------------------------------------------------------------
    def read_pixels(self):
        nc = self.channels()
        mode = self._img.mode
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
                yield tuple([e[c] for c in range(nc)])
        elif mode in ["L", "1"]:
            for e in self._img.getdata():
                yield (e, )
        else:
            for e in self._img.getdata():
                yield tuple([e[c] for c in range(nc)])

    # -------------------------------------------------------------------------
    def pixels(self):
        x = 0
        y = 0
        for pix in self.read_pixels():
            yield x, y, pix
            x += 1
            if x >= self.width():
                x = 0
                y += 1

    # -------------------------------------------------------------------------
    def elements(self, options):
        for x, y, pix in self.pixels():
            e = pix[options.channel] >= options.threshold
            yield x, y, not e if options.invert else e

# ------------------------------------------------------------------------------
class PngImage(object):
    # -------------------------------------------------------------------------
    def __init__(self, options, input_path):
        self._delegate = None
        try:
            import PIL.Image
            png = PIL.Image.open(input_path)
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
    def rows(self, options):
        result = []
        row = None
        for x, y, e in self._delegate.elements(options):
            if x == 0:
                if row is not None:
                    yield row
                row = []
            row.append(e)
        if row is not None:
            yield row

    # -------------------------------------------------------------------------
    def transitions(self, options):
        m = numpy.array([numpy.array(r) for r in self.rows(options)])
        m = m.transpose()
        m = numpy.pad(m, 1, mode='wrap')

        w, h = self.width(), self.height()
        return numpy.array(
            [numpy.array([transition_code(m[x:x+3, y:y+3])
                for x in range(w)]) for y in range(h)])

    # -------------------------------------------------------------------------
    def chunks(self, options):
        y = 0
        for row in self.transitions(options):
            x = 0
            for code in row:
                var = options.variant(x, y, code)
                idx = transition_index(code)
                yield bytes([idx, int(var, 16) if var else 0])

# ------------------------------------------------------------------------------
#  Output conversions
# ------------------------------------------------------------------------------
def convert_eagitexi(options):
    zobj = zlib.compressobj(zlib.Z_BEST_COMPRESSION)
    def _append(img):
        for chunk in img.chunks(options):
            compressed = zobj.compress(chunk)
            if compressed:
                options.write(compressed)

    image0 = PngImage(options, options.input_paths[0])
    if options.output_type == "eagitex":
        options.write('{"levels":1\n')
    else:
        options.write('{"level":1\n')
    options.write(',"width":%d\n' % image0.width())
    options.write(',"height":%d\n' % image0.height())
    if(len(options.input_paths) > 1):
        options.write(',"depth":%d\n' % len(options.input_paths))
    options.write(',"channels":2\n')
    options.write(',"data_type":"unsigned_byte"\n')
    options.write(',"format":"rg"\n')
    options.write(',"iformat":"rg8"\n')
    options.write(',"min_filter":"nearest"\n')
    options.write(',"mag_filter":"nearest"\n')
    options.write(',"wrap_s":"repeat"\n')
    options.write(',"wrap_t":"repeat"\n')
    if(len(options.input_paths) > 1):
        options.write(',"wrap_r":"repeat"')
    options.write(',"data_filter":"zlib"\n')
    options.write('}')
    _append(image0)

    for image_path in options.input_paths[1:]:
        image = PngImage(options, image_path)
        assert image.same_format_as(image0)
        _append(image)

    compressed = zobj.flush()
    if compressed:
        options.write(compressed)

# ------------------------------------------------------------------------------
def convert_html(options):
    options.write('<html>\n')
    options.write('<head>\n')
    options.write('<style>\n')
    options.write('body {background-color: black;}\n')
    options.write('</style>\n')
    options.write('</head>\n')
    options.write('<body>\n')
    for image_path in options.input_paths:
        options.write('<table class="grid">\n')
        image = PngImage(options, image_path)
        y = 0
        for row in image.transitions(options):
            options.write('<tr class="row">\n')
            x = 0
            for code in row:
                var = options.variant(x, y, code)
                options.write('<td class="cell">\n')
                options.write('<img src="%s" alt="%02X%s"/>\n' % ((
                    options.name_format % (code, var)),
                    code, var
                ))
                options.write('</td>\n')
                x += 1
            options.write('</tr>\n')
            y += 1
        options.write('</table>\n')

    options.write('</body>\n')
    options.write('</html>\n')

# ------------------------------------------------------------------------------
def convert_ascii(options):
    for image_path in options.input_paths:
        image = PngImage(options, image_path)
        for row in image.transitions(options):
            options.write(str().join(("%2X" % x) for x in row))
            options.write("\n")

# ------------------------------------------------------------------------------
def convert_orig(options):
    for image_path in options.input_paths:
        image = PngImage(options, image_path)
        options.write("┌" + "──"*image.width() + "┐\n")
        for row in image.rows(options):
            options.write("│"+str().join("▓▓" if v else "  " for v in row)+"│\n")
        options.write("└" + "──"*image.width() + "┘\n")

# ------------------------------------------------------------------------------
def convert(options):
    if options.output_type in ["eagitexi", "eagitex"]:
        convert_eagitexi(options)
    elif options.output_type == "html":
        convert_html(options)
    elif options.output_type == "ascii":
        convert_ascii(options)
    else:
        convert_orig(options)

# ------------------------------------------------------------------------------
#  Other output functions
# ------------------------------------------------------------------------------
def print_combinations(options):
    for c in get_combinations():
        print("%02X" % c)

# ------------------------------------------------------------------------------
def print_missing(options):
    prefix = os.path.dirname(options.output_path)
    for c in get_combinations():
        for v in options.variant.options():
            name = options.name_format % (c, v)
            path = os.path.join(prefix, name)
            if not os.path.isfile(path):
                print(path)
# ------------------------------------------------------------------------------
#  Main function
# ------------------------------------------------------------------------------
def main():
    try:
        options = getArgumentParser().parseArgs()
        if options.print_combinations:
            print_combinations(options)
        elif options.print_missing:
            print_missing(options)
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
