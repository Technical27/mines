{ pkgs ? import <nixpkgs> { } }:

pkgs.mkShell {
  buildInputs = [ ];

  shellHook = ''
    export PATH="/home/aamaruvi/git/Ndless/ndless-sdk/toolchain/install/bin:/home/aamaruvi/git/Ndless/ndless-sdk/bin:$PATH"
  '';
}
