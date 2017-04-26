## Metaprogramming in C++14 and beyond

This repository contains my [reveal.js][]-based presentation on metaprogramming
for the [ACCU 2017][] conference.

## Basic usage
Go to https://ldionne.com/accu-2017-metaprogramming-in-cpp14 or open
`index.html` with your browser (does not work in Chrome). The slides
are also available as a pdf in `slides.pdf`.

## Advanced usage
From the root of the repository,
```sh
npm install
grunt serve &
```

and then connect to `localhost:8000` to view locally.

## Building the code samples

```sh
(mkdir build && cd build && cmake ..)
cmake --build build install-dependencies
cmake --build build
```

<!-- Links -->
[ACCU 2017]: https://conference.accu.org/site/stories/2017/schedule.html
[reveal.js]: https://github.com/hakimel/reveal.js
