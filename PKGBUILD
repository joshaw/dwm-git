pkgname=dwm-git
_pkgname=dwm
pkgver=6.2.r12.ga786211
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
        config.h
        status
        cmds)
md5sums=('SKIP'
         'SKIP'
         'SKIP'
         'SKIP')

pkgver(){
  cd $_pkgname
  git describe --long --tags | sed -E 's/([^-]*-g)/r\1/;s/-/./g'
}

prepare() {
  cd $_pkgname
  git apply ../../dwm-deck-6.2.diff
  git apply ../../dwm-bar-height-6.2.diff
  git apply ../../dwm-statuscmd-nosignal-20210402-67d76bd.diff
  cp ../../config.h config.h
}

build() {
  cd $_pkgname
  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11
}

package() {
  cd $_pkgname
  make PREFIX=/usr DESTDIR="$pkgdir" install

  install -m755 -d "$pkgdir/etc/dwm"
  install -m655 -D ../cmds "$pkgdir/etc/dwm/cmds"
  install -m655 -D ../status "$pkgdir/etc/dwm/status"

  install -m755 -d "$pkgdir/var/log"
}

# vim:set ts=2 sw=2 et:
