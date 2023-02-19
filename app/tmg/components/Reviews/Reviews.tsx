import { Card, CardContent, Grid, Rating, Typography, useMediaQuery } from "@mui/material";
import { useState, useEffect } from "react";

import { REVIEWS } from "content";

import style from "./Reviews.module.scss";

export const Reviews = (): JSX.Element => {

    const isLaptop = useMediaQuery("(max-width: 1440px)");
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
            <Typography variant="h6" className={style.reviews_title}>Testimonials</Typography>
            <Grid
                className={style.reviews}
                container
                spacing={3}
            >
                {REVIEWS.map((review, index: number) => {
                    return (
                        <Grid item key={index} xs={columns}>
                            <Card className={style.reviews_review}>
                                <Typography sx={{ display: "flex", alignItems: "center" }}>
                                    <Rating value={review.rating} sx={{ mx: 2, my: 2}} />
                                    {review.timestamp}
                                </Typography>
                                <CardContent>
                                    {review.content}
                                    <br/><br/>
                                    - {review.author}
                                </CardContent>
                            </Card>
                        </Grid>
                    );
                })}
            </Grid>
        </>
    );
};
