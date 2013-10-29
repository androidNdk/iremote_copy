/**
 * Copyright (c) 2013 Egor Pushkin. All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "Common/Common.h"

#include "ScrollMessage.h"
#include "ScrollMessage2.h"

namespace RemotePC
{
    // {881DD15D-DEF2-42F8-BFD2-52648224384A}
    const mc::Guid ScrollMessage2::messageId_ =
        { 0x881DD15D, 0xDEF2, 0x42F8, { 0xBF, 0xD2, 0x52, 0x64, 0x82, 0x24, 0x38, 0x4A } };

    ScrollMessage2::ScrollMessage2()
        : ScrollMessage()
    {
        mc::MessageImpl::SetCode(ScrollMessage2::messageId_);
    }

    ScrollMessage2::ScrollMessage2( bool vertical, int value )
        : ScrollMessage( vertical, value )
    {
        mc::MessageImpl::SetCode(ScrollMessage2::messageId_);
    }
}
