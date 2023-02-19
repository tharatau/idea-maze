import { Button, Card, CardActions, CardContent, CardHeader, Grid, Typography } from "@mui/material";

import style from "./Footer.module.scss";

export const Footer = (): JSX.Element => {

    return (
        <>
            <Grid container>
                <Grid item xs={6}>
                    <Card sx={{ mx: 2, my: 2, border: "none", boxShadow: "none" }}>
                        <CardHeader>
                            Contact
                        </CardHeader>
                        <CardActions>
                            <Button>
                                CALL NOW
                            </Button>
                        </CardActions>
                        <CardContent>
                            097022 92306
                            <br />
                            087000 96343
                        </CardContent>
                    </Card>
                </Grid>

                <Grid item xs={6}>
                    <Card sx={{ mx: 2, my: 2, border: "none", boxShadow: "none" }}>
                        <CardHeader>
                            Address
                        </CardHeader>
                        <CardActions>
                            <Button>
                                GET DIRECTIONS
                            </Button>
                        </CardActions>
                        <CardContent>
                            H.No. 559, Sector 2, Green Acres Horticultural Society Ranvihir
                            <br />
                            Road, Dolkhamb Taluka Shahapur
                            <br />
                            Dolkhamb, Maharashtra 421601
                            <br />
                            India
                        </CardContent>
                    </Card>
                </Grid>
            </Grid>
        </>
    );
};
