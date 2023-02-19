import { AppBar, Box, Button, Divider, Drawer, IconButton, List, ListItem, ListItemText, Toolbar, Typography } from "@mui/material";
import { Call as CallIcon, Directions as DirectionsIcon, Menu as MenuIcon } from "@mui/icons-material";
import { useState } from "react";

import { HEADER_MENU_ITEMS, HEADER_MENU_TITLE } from "content";

import style from "./Header.module.scss";

export const Header = (): JSX.Element => {

    const [isDrawerOpen, setIsDrawerOpen] = useState(false);

    const handleDrawer = () => {
        setIsDrawerOpen(!isDrawerOpen)
    };

    return (
        <>
            <AppBar className={style.header} component="nav">
                <Toolbar>
                    <IconButton disableRipple color="inherit" onClick={handleDrawer}>
                        <MenuIcon />
                    </IconButton>
                    {isDrawerOpen === false ? (<Typography className={style.header_title} sx={{ mx: 1 }}>
                        {HEADER_MENU_TITLE}
                    </Typography>) : null}
                    <Box sx={{ flexGrow: 1 }} />
                    <Button className={style.header_button} onClick={() => window.location.href = "https://wa.me/+919702292306"}>Book now</Button>
                </Toolbar>
            </AppBar>
            <Drawer
                variant="temporary"
                open={isDrawerOpen}
                onClose={handleDrawer}
                ModalProps={{
                    keepMounted: true, // Better open performance on mobile.
                }}
            >
                <Box sx={{ textAlign: 'center' }}>
                    <Typography className={style.drawer_title} sx={{ my: 2, mx: 2 }} onClick={handleDrawer}>
                        {HEADER_MENU_TITLE}
                    </Typography>
                    <Divider />
                    <List>
                        {HEADER_MENU_ITEMS.map((item: string) => (
                            <ListItem key={item} sx={{ mx: 5 }}>
                                <ListItemText className={style.drawer_item}>{item}</ListItemText>
                            </ListItem>
                        ))}
                    </List>
                </Box>
            </Drawer>
        </>
    );
};
