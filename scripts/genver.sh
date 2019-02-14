#!/usr/bin/env sh
stable="0.0.1"
gitrevs="`git rev-list v$stable..HEAD 2> /dev/null | wc -l)`"
githash="`git rev-parse --short HEAD 2> /dev/null)`"

if [ "$gitrevs" -eq "0" ]; then
    unset gitrevs
fi

if [ -n "$gitrevs" ]; then
    gitrevs=".$gitrevs"
fi

printf "#ifndef VERSION\n#define VERSION \"%s%s-g%s\"\n#endif\n" "$stable" "$gitrevs" "$githash" > ../src/version.h
