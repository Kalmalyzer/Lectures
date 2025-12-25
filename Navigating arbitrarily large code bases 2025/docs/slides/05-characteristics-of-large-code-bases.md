# Characteristics of large code bases

**They have history**. Some parts are old. Some parts are new. A lot has been rewritten over the years.

**They outlive individual programmers**. Programmers come and go; the codebase remains.

**They make up more than one application**. There are helper tools, support services, documentation tools, build systems, etc.

**They do not exist in isolation**. They often interface to other systems. You often need to understand its environment (surrounding services, OSes, compilers/linkers, build systems, users, usage patterns) to understand any part of it sufficiently.
