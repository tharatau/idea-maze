import Image, { StaticImageData } from 'next/image';
import { useState } from 'react';
import Carousel from 'react-material-ui-carousel';

import { CAROUSAL_IMAGES } from 'content';

import style from "./Carousal.module.scss";

export const Carousal = (): JSX.Element => {
    const [images, setImages] = useState<StaticImageData[]>(CAROUSAL_IMAGES);
    return (
        <Carousel
            className={style.carousal}
            navButtonsAlwaysVisible={true}
            animation="slide"
            interval={5000}
        >
            {images.map((image: StaticImageData, index: number) => {
                return (
                    <Image alt="" className={style.image} key={index} src={image} />
                )
            })}
        </Carousel>
    );
};