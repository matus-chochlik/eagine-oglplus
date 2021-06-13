#!/usr/bin/env bash
# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
wd="$(dirname ${0})"

exec 1>${wd}/Sources.cmake 
cat << EOD
# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
EOD

echo "set(HEADERS"
find ${wd}/eagine -type f -name *.hpp -print |\
	sed -n "s|^${wd}/\(.*\)$|    \1|p" | sort | uniq
echo ")"
echo
echo "set(PUB_INLS"
find ${wd}/eagine -type f -name *.inl -exec \
	grep -H -c -e EAGINE_LIB_FUNC {} \; |\
	sed -n "s|^${wd}/\(.*\):0$|    \1|p" | sort | uniq
echo ")"
echo
echo "set(LIB_INLS"
find $(dirname ${0})/eagine -type f -name *.inl -exec \
	grep -H -c -e EAGINE_LIB_FUNC {} \; |\
	sed -n "s|^${wd}/\(.*\):[1-9][0-9]*$|    \1|p" | sort | uniq
echo ")"
echo

