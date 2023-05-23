Group Members
---
* Gregory N. Schmit

Progress Since Last Report
---
* Wrote a template function `route` that concatenates arguments to a path
* Built a small test app to write test cases
* Rather than `String` casting (what I originally did), used `.toString()` to
  convert the `Object`s to `String`s
* Replied to the issue to see if my implementation would meet the desired
  functionality.

Problems Encountered
---
* First I had to learn the difference between writing a template `filter` and a
  template `function`.
* I initially casted the arguments to `String`, however this would cause a
  runtime error when `Integer`s were passed, since they cannot be casted to
  `String` since they are neither a subclass or superclass. I ended up finding
  out that `Object` implements `.toString()` so it was safe to use for any
  Object that is passed, so I used it to interpret arguments as `String`s.

Next Steps
---
* Verify that the functionality I implemented is actually what they were looking for.
