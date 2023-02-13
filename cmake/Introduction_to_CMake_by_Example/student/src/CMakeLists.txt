# PRIVATE sources are added to the SOURCES property. INTERFACE sources are added to the
# INTERFACE_SOURCES property. PUBLIC sources are added to both properties. The more practical way of
# thinking of this is that PRIVATE sources are compiled into targetName , INTERFACE sources are added to
# anything that links to targetName and PUBLIC sources are added to both. In practice, anything other
# than PRIVATE would be unusual. Section 18.2.4, “Interface Libraries” discusses scenarios where
# listing headers with INTERFACE may be justified if supporting CMake 3.18 or earlier.
target_sources(mainapp PRIVATE Student.cpp Student.h)
