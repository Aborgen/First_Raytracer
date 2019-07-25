# First_Raytracer
This is my foray into the field of Computer Graphics, as well as my first real project written in c++. I have always been fascinated by the process behind how 3d images are rendered, so I am glad that the course from edX gave me the push I needed to apply my programming knowledge toward some interesting topics.

The third and final project had us create a raytracer from scratch. Below are some images that were generated from instructions that were provided to us in source files written by the instructor. Within the file, there are various keywords that needed to be parsed such as:<br />  
**size 640 480
<img src="https://user-images.githubusercontent.com/28365047/61838678-44165e00-ae3f-11e9-906a-bbb5f8e196a8.png" align="left" width="200"></img><br />
camera 0 0 0 0 0 -1 0 1 0 45<br />
output scene.png<br />
ambient 0 1 0<br />
translate 0 0 -5<br />
sphere 0 0 0 1**

This can be read as:  
**size width height**<br />
**camera eyePosition center up fovy**<br />
(eyePosition, center, and up are vectors in ℝ<sup>3</sup>, while fovy is assumed to be in degrees)<br />
**ambient r g b**<br />
**translate x y z**<br />
**sphere x y z radius**

The result, if everything is working properly, is a set of images that should be nearly--if not exactly--the same as the reference images which we are automatically graded against.

<img src="https://user-images.githubusercontent.com/28365047/61836395-e41aba00-ae34-11e9-8680-6342b520d312.png" width="300"></img>
<img src="https://user-images.githubusercontent.com/28365047/61836404-ebda5e80-ae34-11e9-821a-90ea307fb61a.png" width="300"></img>

<img src="https://user-images.githubusercontent.com/28365047/61837320-18907500-ae39-11e9-8e2f-e88f8806a205.png" width="300"></img>
<img src="https://user-images.githubusercontent.com/28365047/61837588-42966700-ae3a-11e9-9cf4-7d11d7dfb652.png" width="300"></img>
