# adk_yocto

How use?

git clone git@github.com:trotill/adk_yocto.git

cd adk_yocto/
$: MACHINE=adakta-adk DISTRO=fslc-x11 source setup-environment build/

Then create your own distro or compile a demo
core-image-minimal
core-image-sato
core-image-x11

For example
$: bitbake core-image-minimal

Copy core-image-minimal.gz to uSD card.
