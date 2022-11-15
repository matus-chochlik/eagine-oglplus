#!/bin/bash
# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
in_r=${1:-red.png}
in_g=${2:-green.png}
in_b=${3:-blue.png}
out=${4:-rgb.png}

convert \
	"${in_r}" "${in_g}" ${in_b}" \
	"-channel"    "RGB" \
	"-colorspace" "RGB" \
	"-combine" "${out}"
