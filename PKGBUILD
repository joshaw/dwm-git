pkgname=dwm-git
_pkgname=dwm
pkgver=6.4.r6.g9f88553
pkgrel=1
pkgdesc="A dynamic window manager for X"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
options=(!strip zipman)
depends=('libx11' 'libxinerama' 'libxft')
makedepends=('git' 'gcc')
provides=('dwm')
conflicts=('dwm')
source=("$_pkgname::git+http://git.suckless.org/dwm"
        dwm-deck-6.2.diff
        dwm-statuscmd-nosignal.diff
        dwm-statusallmons-6.4.diff
        config.h)
md5sums=('SKIP'
         'SKIP'
         'SKIP'
         'SKIP'
         'SKIP')

pkgver(){
  cd $_pkgname
  git describe --long --tags | sed -E 's/([^-]*-g)/r\1/;s/-/./g'
}

__log() {
  echo "About to run command: $*"
  "$@"
}

prepare() {
  cd $_pkgname
  __log git apply -v ../../dwm-statuscmd-nosignal.diff
  __log git apply -v ../../dwm-deck-6.2.diff
  __log git apply -v ../../dwm-statusallmons-6.4.diff
  cp ../../config.h config.h
}

build() {
  cd $_pkgname
  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11
}

package() {
  cd $_pkgname
  make PREFIX=/usr DESTDIR="$pkgdir" install
}

# vim:set ts=2 sw=2 et:
