## Chapter 10: Going Deeper with Advanced Static Analysis

### vmlinux
- 현재 커널의 **dbg** 패키지를 설치해 사용하면 된다.
```shell
sudo atp install linux-image-$(uname -r)-dbg
file /usr/lib/debug/boot/*
```

``` 
/usr/lib/debug/boot/System.map-6.12.57+deb13-arm64: ASCII text
/usr/lib/debug/boot/vmlinux-6.12.57+deb13-arm64:    ELF 64-bit LSB shared object, ARM aarch64, version 1 (SYSV), statically linked, BuildID[sha1]=3f83ccb69318a9e82747d67f949846d8e6a9ccb4, with debug_info, not stripped
```
