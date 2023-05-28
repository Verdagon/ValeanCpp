# Valean C++ Library

This is a tiny C++ library inspired by [Vale](https://vale.dev)'s memory management scheme. Included are two techniques:

 * `cref` "constraint references" where, upon destruction, an object asserts that no constraint references are pointing at it.
 * `vref` "vale references" where we compare the reference's remembered "key" to the one held by the target object.

Both of these, when combined with C++'s basic single ownership, help with memory safety.

Check out https://verdagon.dev/blog/vale-memory-safe-cpp for more.

Note that this is NOT production ready, merely a proof of concept. Happy to accept contributions from anyone who wants to make it into a serious library.
