This is a small example project demonstrating how to use [DetourCreateProcessWithDllEx](https://github.com/microsoft/Detours/wiki/DetourCreateProcessWithDllEx) in [Microsoft Detours](https://github.com/microsoft/Detours).

## Structure

- `DetoursTarget` is our target application, which does no more than a `ShowMessage` call.
- `DetoursHook` is the DLL that we're going to attach to it, which intercepts that `ShowMessage` call and dumps it into `stdout` instead.
- `DetoursTest` is the project that's going to run `DetoursTest` with `DetoursHook` attached.

## Building

- Build Detours by opening Developer Command Prompt for your according Visual Studio version, `cd`-ing to Detours directory, and running `nmake`.
- Copy x86 `detours.lib` and `detours.pdb` to `DetoursTest/` and `DetoursHook/` directories.
- Open `DetoursTest.sln`, build solution for x86, then run.

## Key points

- Much like normal `CreateProcess`, `DetourCreateProcessWithDllEx` takes an absolute path for first argument.
- DLL name argument can be (should be? It's non-Unicode) a relative path if the DLL is in the target application directory.
- The "DLL must contain an exported function with ordinal #1." part of documentation means that you need to add a `.def` file (here, `detours.def`) and point it at some `BOOL APIENTRY` function that doesn't seem to be actually get called or anything.

