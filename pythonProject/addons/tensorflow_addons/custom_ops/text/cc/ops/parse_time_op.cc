/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "tensorflow/core/framework/common_shape_fns.h"
#include "tensorflow/core/framework/op.h"

namespace tensorflow {
namespace addons {
REGISTER_OP("Addons>ParseTime")
    .Input("time_string: string")
    .Output("time_int64: int64")
    .Attr("time_format: string")
    .Attr("output_unit: {'SECOND', 'MILLISECOND', 'MICROSECOND', 'NANOSECOND'}")
    .SetShapeFn(tensorflow::shape_inference::UnchangedShape)
    .Doc(R"doc(
Parse an input string according to the provided format string into a Unix time,
the number of seconds / milliseconds / microseconds / nanoseconds elapsed since
January 1, 1970 UTC.

Uses strftime()-like formatting options, with the same extensions as
FormatTime(), but with the exceptions that %E#S is interpreted as %E*S, and %E#f
as %E*f.  %Ez and %E*z also accept the same inputs.

%Y consumes as many numeric characters as it can, so the matching data should
always be terminated with a non-numeric.  %E4Y always consumes exactly four
characters, including any sign.

Unspecified fields are taken from the default date and time of ...

  "1970-01-01 00:00:00.0 +0000"

For example, parsing a string of "15:45" (%H:%M) will return an Unix time that
represents "1970-01-01 15:45:00.0 +0000".

Note that ParseTime only heeds the fields year, month, day, hour, minute,
(fractional) second, and UTC offset.  Other fields, like weekday (%a or %A),
while parsed for syntactic validity, are ignored in the conversion.

Date and time fields that are out-of-range will be treated as errors rather than
normalizing them like `absl::CivilSecond` does.  For example, it is an error to
parse the date "Oct 32, 2013" because 32 is out of range.

A leap second of ":60" is normalized to ":00" of the following minute with
fractional seconds discarded.  The following table shows how the given seconds
and subseconds will be parsed:

  "59.x" -> 59.x  // exact
  "60.x" -> 00.0  // normalized
  "00.x" -> 00.x  // exact

time_string: the input time string to be parsed.
time_format: the time format.
time_int64: the number of seconds / milliseconds / microseconds / nanoseconds
  elapsed since January 1, 1970 UTC.
output_unit: the output unit of the parsed unix time. Can only be SECOND,
  MILLISECOND, MICROSECOND, NANOSECOND.
)doc");
}  // end namespace addons
}  // end namespace tensorflow
