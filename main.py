import cv2
import numpy as np

src = cv2.imread("shapes.jpg", cv2.IMREAD_COLOR)
cv2.imshow("IMREAD_COLOR", src)

gray = cv2.cvtColor(src, cv2.COLOR_RGB2GRAY)
cv2.imshow("COLOR_RGB2GRAY", gray)

ret, binary = cv2.threshold(gray, 200, 255, cv2.THRESH_BINARY)
cv2.imshow("binary", binary)

binary = cv2.bitwise_not(binary)
cv2.imshow("bitwise_not", binary)

contours, hierarchy = cv2.findContours(binary, cv2.RETR_CCOMP, cv2.CHAIN_APPROX_NONE)[-2:]

cv2.drawContours(src, contours, -1, (255, 0, 0), 4)
cv2.imshow("drawContours", src)

for i in range(len(contours)):
    epsilon = 0.01 * cv2.arcLength(contours[i], True)
    approx = cv2.approxPolyDP(contours[i], epsilon, True)

    cv2.drawContours(src, [approx], 0, (0, 0, 255), 2)

    contour_area = len(approx)
    cv2.putText(src, "index is ="+str(i),(approx[0][0][0], approx[0][0][1] + 30), cv2.FONT_HERSHEY_COMPLEX, 0.8, (0, 255, 0), 1)
    cv2.putText(src, str(contour_area), tuple(approx[0][0]), cv2.FONT_HERSHEY_COMPLEX, 0.8, (0, 255, 0), 1)


    if contour_area==4:
        print("square")
        cv2.putText(src, "square", (approx[0][0][0], approx[0][0][1] + 50), cv2.FONT_HERSHEY_COMPLEX, 0.8,(0, 255, 0), 1)
    elif contour_area==3 :
        print("triangle")
        cv2.putText(src,"triangle", (approx[0][0][0], approx[0][0][1] + 50), cv2.FONT_HERSHEY_COMPLEX, 0.8,(0, 255, 0), 1)
    elif contour_area>10:
        print("circle")
        cv2.putText(src,"circle", (approx[0][0][0], approx[0][0][1] + 50), cv2.FONT_HERSHEY_COMPLEX, 0.8,(0, 255, 0), 1)
    else:
         print("지정되지않은 도형")

cv2.imshow("src", src)
cv2.waitKey(0)
cv2.destroyAllWindows()
