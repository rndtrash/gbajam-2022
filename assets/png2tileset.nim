import trick

let bg = loadBg4("disclaimer.png")
writeFile("disclaimer.map.bin", toBytes(bg.map))
writeFile("disclaimer.img.bin", toBytes(bg.img))
writeFile("disclaimer.pal.bin", toBytes(joinPalettes(bg.pals)))
