# hare/wrap/ header files

The "resource acquisition is initialization" technique is the appropriate
C++ way to ensure closing all requested system ressources.

[Bjarne Stroustrup about that](https://www.stroustrup.com/bs_faq2.html#finally)

In GUI programming I would also recommend this technique to deactivate
a wait cursor - maybe including a static usage counter.
