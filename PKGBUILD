pkgname=hp11em
pkgver=0.0.5
pkgrel=1
pkgdesc="A (incomplete) GTK, linux, HP11C calculator emulator"
arch=('i686' 'x86_64')
url="http://www.rapgenic.it/wp/hp11em/"
license=('GPL3')
depends=('gtkmm3')
makedepends=('git')
source=("https://github.com/rapgenic/$pkgname/archive/v$pkgver.tar.gz")

build() {
        cd "$pkgname-$pkgver"
        ./autogen.sh
        ./configure --prefix=/usr
        make
}

package() {
        cd "$pkgname-$pkgver"
        make DESTDIR="$pkgdir/" install
}

sha256sums=('SKIP')
