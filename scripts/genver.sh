#!/usr/bin/env bash
version="0.0.4"
stable=0
gitrevs="`git rev-list v$version..HEAD 2> /dev/null | wc -l`"
githash="`git rev-parse --short HEAD 2> /dev/null`"
file="../src/version.h"

if [ "$gitrevs" -eq "0" ]; then
    unset gitrevs
fi

if [ -n "$gitrevs" ]; then
    gitrevs=".$gitrevs"
fi

if let $stable; then
    printf "#ifndef VERSION\n#define VERSION \"$version\"\n#endif" > $file
else
    printf "#ifndef VERSION\n#define VERSION \"%s%s-g%s\"\n#endif" "$version" "$gitrevs" "$githash" > $file
fi
