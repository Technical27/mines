{ pkgs ? import <nixpkgs> { } }:

pkgs.mkShell rec {
  buildInputs = [ ];

  # GENZEHN_DEPS = with pkgs; "${zlib}/lib:${boost}/lib:${stdenv.cc.cc.lib}/lib";
  # GCC_DEPS = with pkgs; "${zlib}/lib:${stdenv.cc.cc.lib}/lib";
  # OTHER_DEPS = with pkgs; "${GCC_DEPS}:${libmpc}/lib:${mpfr}/lib:${gmp}/lib";


  # patchelf --set-rpath $GENZEHN_DEPS /home/aamaruvi/git/Ndless/ndless-sdk/bin/genzehn

  # for file in /home/aamaruvi/git/Ndless/ndless-sdk/toolchain/install/bin/*; do
  #   patchelf --set-rpath $GCC_DEPS $file
  # done

  # patchelf --set-rpath $OTHER_DEPS /home/aamaruvi/git/Ndless/ndless-sdk/toolchain/install/bin/arm-none-eabi-lto-dump

  # patchelf --set-rpath $OTHER_DEPS /home/aamaruvi/git/Ndless/ndless-sdk/toolchain/install/bin/arm-none-eabi-gdb

  shellHook = with pkgs; ''
    export LD_LIBRARY_PATH="${zlib}/lib:${boost}/lib:${stdenv.cc.cc.lib}/lib:${libmpc}/lib:${mpfr}/lib:${gmp}/lib"
    export PATH="/home/aamaruvi/git/Ndless/ndless-sdk/toolchain/install/bin:/home/aamaruvi/git/Ndless/ndless-sdk/bin:$PATH"
  '';
}
