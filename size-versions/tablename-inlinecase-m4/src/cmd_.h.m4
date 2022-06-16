WithLicense(`MIT License

Copyright (c) 2022 groboclown

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.')
AsOptional(`chmod', `

#include <sys/stat.h>
#include <fcntl.h>

#include "force-inline.h"
#include "output.h"
#include "globals.h"
#include "helpers.h"

WithNamedStep(XX, "xx", `
    OnInit(
        LOG(":: init xx");
    )
    OnCmd(
        LOG(":: xx start");
    )
    OnArg(
        LOG(":: xx arg ");
        LOGLN(global_arg);
    )
')
WithVirtualStep(XX_RUN, `
    OnArg(
        LOG(":: xx on ");
        LOGLN(global_arg);
    )
')

/* End Optional Command */
')