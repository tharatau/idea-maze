import { Card, CardContent, Grid, Typography, useMediaQuery } from "@mui/material";
import Image from "next/image";
import { useEffect, useState } from "react";

import { GALLERY_IMAGES } from "content";

import style from "./Gallery.module.scss";

export const Gallery = (): JSX.Element => {

    const isLaptop = useMediaQuery("(max-width: 1024px)");
    const isTablet = useMediaQuery("(max-width: 768px)");
    const isMobile = useMediaQuery("(max-width: 425px)");

    const [columns, setColumns] = useState(3);

    useEffect(() => {
        if (isLaptop === true) {
            setColumns(4);
        }
        if (isTablet === true) {
            setColumns(6);
        }
        if (isMobile === true) {
            setColumns(12);
        }
    }, [isLaptop, isTablet, isMobile]);


    return (
        <>
            <Typography variant="h6" className={style.gallery_title}>
                Gallery
            </Typography>
            <Grid
                className={style.reviews}
                container
                spacing={3}
            >
                {GALLERY_IMAGES.map((image, index: number) => {
                    return (
                        <Grid item key={index} xs={columns}>
                            <Card elevation={0}>
                                <CardContent>
                                    <Image
                                        src={image}
                                        alt={""}
                                        className={style.gallery_image}
                                    />
                                </CardContent>
                            </Card>
                        </Grid>
                    );
                })}
            </Grid>
        </>
    );
};