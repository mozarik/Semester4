function ukuranKotak() {
    const element = document.querySelector('.kotak')
    const style = getComputedStyle(element)
    const height = style.getPropertyValue('height').slice(0, 3)
    const widht = style.getPropertyValue('width').slice(0, 3)
    const text = `Ukurang kotak sekarang adalah ${height} x ${widht}`
    alert(text)
}

function ubahUkuran() {
    const panjang = document.getElementById("panjang-text").value
    const lebar = document.getElementById("lebar-text").value
    console.log(panjang, lebar);

    document.getElementsByClassName("kotak")[0].style.width = panjang
    document.getElementsByClassName("kotak")[0].style.height = lebar

}


var warna = ["red", "green", "blue", "yellow", "magenta"]
var i = 0
document.getElementById("warna-kotak").addEventListener("click", function () {
    i = i < warna.length ? ++i : 0
    document.getElementsByClassName("kotak")[0].style.background = warna[i]
})