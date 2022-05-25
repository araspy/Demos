import React from 'react'
import CustomBtn from './CustomBtn'
import logo from '../logo.svg'
import logoMobile from '../logoMobile.svg'
import Popup from './Popup'
import { useState } from 'react';
import {Toolbar, Typography} from '@material-ui/core'
import {makeStyles} from "@material-ui/core/styles"; 

const styles = makeStyles({
    bar:{
        paddingTop: "1.15rem",
        backgroundColor: "#fff",
        ['@media (max-width:780px)']: { 
           flexDirection: "column"
          }
    },
    logo: {
        width: "8%", 
        ['@media (max-width:780px)']: { 
           display: "none"
           }
    },
    logoMobile:{
        width: "100%", 
        display: "none", 
        ['@media (max-width:780px)']: { 
            display: "inline-block"
            }
    },
    menuItem: {
        cursor: "pointer", 
        flexGrow: 1,
        "&:hover": {
            color:  "#00d595"
        },
        ['@media (max-width:780px)']: { 
            paddingBottom: "1rem"    }
    }
})

function NavBar() {
    const [buttonPopup, setButtonPopup] = useState(false);
    const classes = styles()
    return (
            <Toolbar position="sticky" color="rgba(0, 0, 0, 0.87)" className={classes.bar}>   
                <img src={logo} className={classes.logo}/> 
                <img src={logoMobile} className={classes.logoMobile}/>
                Stockr.
                <Typography variant="h6" className={classes.menuItem}>
                    About
                </Typography>
                <Typography variant="h6" className={classes.menuItem}>
                    Updates
                </Typography>
                <Typography variant="h6" className={classes.menuItem}>
                    Contact Us
                </Typography>
                <CustomBtn txt="Settings" onClick={() => setButtonPopup(true)}/>
                <Popup trigger={buttonPopup} setTrigger={setButtonPopup}>
                    <h3>Place settings here</h3>
                    <p>asl;kfja;lwkj</p>
                </Popup>
            </Toolbar>
    )
}

export default NavBar