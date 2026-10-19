A simple, classical motion tracker for a static camera. MOG2 background subtraction learns the scene and produces a mask of changed pixels. Contours (blobs) of that mask are filtered by size, and the one nearest the center of a 350x350 region is picked. After it has been seen for about half a second, a CSRT tracker locks on and follows the object with a box. No AI or training is involved.


ISSUE:
- MOG2 assumes each pixel position keeps showing the same part of the scene. When a PTZ camera pans, tilts or zooms, every pixel suddenly shows something different. The whole frame then looks like foreground, and the mask lights up everywhere. The model does eventually relearn, but while the camera is moving it never settles, so there’s no usable background to compare against.
- MOG2 assumes a static camera. If the camera moves (for example a PTZ pan, tilt or zoom), every pixel changes, so the whole frame is flagged as motion and the learned background is invalidated. The tracker can’t separate the moving object from the moving view.


SOLUTION:
- 3 frame masking. 3 pictures, initial, middle, end, mask initial to middle and end to middle and then AND the 2 masks to get one big blob/contour of the 2 masks, and draw from the corners a rectangle, a bounding box. THIS CAN FAIL IF THE OBJ IS MOVING TO FAST AND MASK IS TO LARGE(mask to large, over 50% of captured image will be thrown away bc of error)(error is if camera moved and entire or part of screen becomes a white mask because all the scene changed).
