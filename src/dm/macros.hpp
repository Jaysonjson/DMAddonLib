#ifndef MACROS_H
#define MACROS_H
#define EXTRACT(x, n, J) if (J.contains(n)) x = J[n].get<decltype(x)>()
#define EXTRACT_VAR(x, J) if (J.contains(#x)) x = J[#x].get<decltype(x)>()
#endif // MACROS_H
