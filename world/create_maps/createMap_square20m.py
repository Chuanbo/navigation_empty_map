#!/usr/bin/env python
# -*- coding: utf-8 -*-

from PIL import Image, ImageDraw

white_color = 254
grey_color = 205
black_color = 0

mapImage = Image.new("L", (400,400), white_color)
draw = ImageDraw.Draw(mapImage)  # 定义画图对象 


# 在图像的边缘画上黑边，以在Stage仿真时界定地图范围 
box = (0, 0, 5, 400)
draw.rectangle( box, outline=black_color, fill=black_color )
box = (0, 394, 400, 400)
draw.rectangle( box, outline=black_color, fill=black_color )
box = (394, 0, 400, 400)
draw.rectangle( box, outline=black_color, fill=black_color )
box = (0, 0, 400, 5)
draw.rectangle( box, outline=black_color, fill=black_color )


del draw  # 释放画图对象所占内存 

mapImage.show()

mapImage.save("/home/exbot/square20m.pgm")
