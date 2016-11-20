#!/usr/bin/env python
# -*- coding: utf-8 -*-

from PIL import Image, ImageDraw

white_color = 254
grey_color = 205
black_color = 0

mapImage = Image.new("L", (700,330), white_color)
draw = ImageDraw.Draw(mapImage)  # 定义画图对象 


box = (50, 50, 652, 56)  # 1 
draw.rectangle( box, outline=black_color, fill=black_color )
box = (646, 56, 652, 109)  # 2 
draw.rectangle( box, outline=black_color, fill=black_color )
box = (218, 103, 646, 109)  # 3 
draw.rectangle( box, outline=black_color, fill=black_color )
box = (218, 109, 224, 123)  # 4 
draw.rectangle( box, outline=black_color, fill=black_color )
box = (203, 123, 224, 129)  # 5 
draw.rectangle( box, outline=black_color, fill=black_color )
box = (203, 129, 209, 289)  # 6 
draw.rectangle( box, outline=black_color, fill=black_color )
box = (56, 283, 203, 289)  # 7 
draw.rectangle( box, outline=black_color, fill=black_color )
box = (50, 56, 56, 289)  # 8 
draw.rectangle( box, outline=black_color, fill=black_color )

box = (140, 210, 170, 238)  # 9 
draw.rectangle( box, outline=black_color, fill=black_color )

box = (0, 0, 700, 49)  # 10 
draw.rectangle( box, outline=grey_color, fill=grey_color )
box = (653, 50, 700, 330)  # 11 
draw.rectangle( box, outline=grey_color, fill=grey_color )
box = (225, 110, 652, 330)  # 12 
draw.rectangle( box, outline=grey_color, fill=grey_color )
box = (210, 130, 224, 330)  # 13 
draw.rectangle( box, outline=grey_color, fill=grey_color )
box = (50, 290, 209, 330)  # 14 
draw.rectangle( box, outline=grey_color, fill=grey_color )
box = (0, 50, 49, 330)  # 15 
draw.rectangle( box, outline=grey_color, fill=grey_color )

# 在图像的四个角画上黑色小方格，以在Stage仿真时界定地图范围 
box = (0, 0, 5, 5)
draw.rectangle( box, outline=black_color, fill=black_color )
box = (694, 0, 700, 5)
draw.rectangle( box, outline=black_color, fill=black_color )
box = (694, 324, 700, 330)
draw.rectangle( box, outline=black_color, fill=black_color )
box = (0, 324, 5, 330)
draw.rectangle( box, outline=black_color, fill=black_color )


del draw  # 释放画图对象所占内存 

mapImage.show()

mapImage.save("corridor.pgm")
