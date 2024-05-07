# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/shado/QT/NefaryousGame/cmake-build-debug/_deps/ds-src"
  "C:/Users/shado/QT/NefaryousGame/cmake-build-debug/_deps/ds-build"
  "C:/Users/shado/QT/NefaryousGame/cmake-build-debug/_deps/ds-subbuild/ds-populate-prefix"
  "C:/Users/shado/QT/NefaryousGame/cmake-build-debug/_deps/ds-subbuild/ds-populate-prefix/tmp"
  "C:/Users/shado/QT/NefaryousGame/cmake-build-debug/_deps/ds-subbuild/ds-populate-prefix/src/ds-populate-stamp"
  "C:/Users/shado/QT/NefaryousGame/cmake-build-debug/_deps/ds-subbuild/ds-populate-prefix/src"
  "C:/Users/shado/QT/NefaryousGame/cmake-build-debug/_deps/ds-subbuild/ds-populate-prefix/src/ds-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/shado/QT/NefaryousGame/cmake-build-debug/_deps/ds-subbuild/ds-populate-prefix/src/ds-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/shado/QT/NefaryousGame/cmake-build-debug/_deps/ds-subbuild/ds-populate-prefix/src/ds-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
