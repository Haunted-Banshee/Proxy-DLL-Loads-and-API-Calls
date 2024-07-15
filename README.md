# Proxy-DLL-Loads-and-API-Calls

This repository includes POCs demonstrating how to proxy DLL loads and API calls using SimpleCallback.

### Compile
```
ml64 /c /Fo Helper.obj Helper.asm
cl /EHsc SimpleCallback.cpp Helper.obj
```


### References

- https://learn.microsoft.com/en-us/previous-versions/windows/desktop/legacy/ms686295(v=vs.85)
* https://0xdarkvortex.dev/proxying-dll-loads-for-hiding-etwti-stack-tracing/
+ https://0xdarkvortex.dev/hiding-in-plainsight/
