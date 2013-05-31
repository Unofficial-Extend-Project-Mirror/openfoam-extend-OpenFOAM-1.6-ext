#!/bin/sh

# TODO: checkout correct tag
GPGKey=${1}
ubuntuVersion="10.04"
myTag="0c3137b5"
pushOrigSources="-sa" ## yes
# pushOrigSources="-sd" ## no

## update branch to the desired tag
git merge ${myTag}

## or reset branch to the desired tag (this could lead to file losses)
# git reset --merge ${myTag}

## create debian changelog for a release
# git-dch --release
## or for a snapshot
# git-dch --snapshot


## create debian source package with *.orig.tar.gz and patches
git-buildpackage \
	--git-builder="debuild -i\.git -I.git -S ${pushOrigSources} -k${GPGKey}" \
	--git-upstream-branch=master \
	--git-debian-branch=packaging/ubuntu/${ubuntuVersion} \
	--git-ignore-new

## build debian source package in pbuilder
# sudo pbuilder build --pkgname-logfile ../openfoam-1.6-ext_1.6.0-1ppa1~lucid1.dsc