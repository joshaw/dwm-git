pkgname=dwm-git
_pkgname=dwm
pkgver=6.3.r2.gbece862
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
        dwm-bar-height-6.2.diff
        dwm-statuscmd-nosignal-20210402-67d76bd.diff
        dwm-statusallmons-6.2.diff
        config.h
        status
        cmds)
md5sums=('SKIP'
         '0f8f3afce44741b4a017a36523060efe'
         'f54440d2d8c238a935f59742e7589abc'
         'ba677b134f454aaa0c36814808d623f3'
         'c45eb8600c0931781032192c50eccec6'
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
  git apply ../../dwm-statusallmons-6.2.diff
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
}

# vim:set ts=2 sw=2 et:
