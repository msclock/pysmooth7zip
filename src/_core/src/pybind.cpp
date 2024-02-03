#include <pybind11/pybind11.h>
#include "_core.hpp"

#define STRINGIFY(x)       #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

PYBIND11_MODULE(_core, m) {
    m.doc() = R"pbdoc(
      Pybind11 _core plugin
      -----------------------
      .. currentmodule:: _core
      .. autosummary::
         :toctree: _generate
         add
  )pbdoc";

    m.attr("__version__") = _core::ProjectVersion();
}
