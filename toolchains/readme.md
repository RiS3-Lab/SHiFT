
# Precompiled toolchains

 To download the precompiled binaries, please follow the instructions [here.](https://4sksufrafeuvtpokf7jrjvwz340wgons.lambda-url.us-east-1.on.aws/)


# How to build a modified arm toolchain by yourself:

1. First you need to build the standard ARM GNU toolchain provided by ARM according to the Release Notes that you can find here 
https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads


The instructions uses the Linaro ABE (Advanced Build Environment), thus you need to have a 
Linux hosting machine. Notice that you can build different ARM flavors using differen manifest for ABE. We used the arm-gnu-toolchain-arm-none-eabi-abe-manifest.txt  also provided by ARM in the same webpage linked above


2. After you succesfully built the standard ARM GNU toolchain navigate to the snapshots in the build directory (the original compilation build folder used with abe). It should contain the snapshots of all the tarballs downloaded acccording to the manifest.
 


3. Calculate the offset according to the details in Table 2 of our paper https://www.usenix.org/system/files/usenixsecurity24-mera.pdf


4. Modify the value returned by the "arm_asan_shadow_offset" function in the gcc/gcc/config/arm/arm.cc file, according to the calculated offset in step 3. Due to the different versions of GCC we cannot publish a patch for these changes. Simply look for the aforementioned function and perform the described changes. For example:
   
     
```
/* Implement the TARGET_ASAN_SHADOW_OFFSET hook.  */

static unsigned HOST_WIDE_INT
arm_asan_shadow_offset (void)
{
  //return HOST_WIDE_INT_1U << 29; //Previous value
  return 0x1c020000;  // New value
}
```


5. Compress the GCC folder with the new changes and replace the previously downloaded tarball with the new compresed file
	gcc.tar.xz
6. Calculate the MD5 digest for the tarball within the same folder
	md5sum gcc.tar.xz > gcc.tar.xz.asc

7. Create a new bulding folder (e.g., build2) at the same level of the "build" folder that contains the snapshots, and build the toolcahin using the local snapshots including the modified tarball for GCC. 

```
cd ..
mkdir build2
cd build2
cp ../arm-gnu-toolchain-arm-none-eabi-abe-manifest.txt .
../abe/configure --with-local-snapshots={full path root GCC building folder}/build/snapshots
../abe/abe.sh --manifest ../arm-gnu-toolchain-arm-none-eabi-abe-manifest.txt --build all  --disable update
```

# Notes:
- You need to disable updates (--disable update) to force "abe.sh" to use the local modified snapshots for GCC
- The provided commands assume that your building tree looks like:

  {full path root GCC building folder}/abe/

  {full path root GCC building folder}/toolchain-arm-none-eabi-abe-manifest.txt

  {full path root GCC building folder}/build/snapshots

  {full path root GCC building folder}/build2

