# Vendored third-party sources

```
cmsis-core       STMicroelectronics/cmsis-core        tag v5.6.0_cm4   Apache-2.0
cmsis-device-l4  STMicroelectronics/cmsis-device-l4   tag v1.7.5       Apache-2.0
```

Unmodified upstream copies. Only `Include/` is vendored.

`system_stm32l4xx.c` and `startup_stm32l4r5xx.s` in the repo root come from the same
cmsis-device-l4 tag and must be updated together with these headers.

Each package keeps its upstream license file alongside the headers:
`cmsis-core/LICENSE.txt` and `cmsis-device-l4/LICENSE.md`.

## Refreshing

```sh
tmp=$(mktemp -d)
git clone --depth 1 -b v1.7.5 https://github.com/STMicroelectronics/cmsis-device-l4 "$tmp/dev"
git clone --depth 1 -b v5.6.0_cm4 https://github.com/STMicroelectronics/cmsis-core "$tmp/core"

cp "$tmp"/dev/Include/{stm32l4xx.h,stm32l4r5xx.h,system_stm32l4xx.h} third_party/cmsis-device-l4/Include/
cp "$tmp"/dev/LICENSE.md third_party/cmsis-device-l4/
cp "$tmp"/core/Include/*.h third_party/cmsis-core/Include/
cp "$tmp"/core/LICENSE.txt third_party/cmsis-core/

cp "$tmp"/dev/Source/Templates/system_stm32l4xx.c .
cp "$tmp"/dev/Source/Templates/gcc/startup_stm32l4r5xx.s .

rm -rf "$tmp"
```

## Version note

ST's compatibility table in the cmsis-device-l4 README pairs device tags with core
tags, but it stops at device `v1.7.2`. There is no documented pairing for `v1.7.3`
and later, and cmsis-core has no `_cm4` tag after `v5.6.0_cm4`, so `v5.6.0_cm4` is
carried forward here.

Device `v1.7.2` and earlier are BSD-3-Clause; `v1.7.3` onwards are Apache-2.0.
