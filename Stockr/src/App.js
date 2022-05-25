import { createTheme, ThemeProvider, makeStyles } from '@material-ui/core/styles';
import {Typography} from '@material-ui/core'; 
import NavBar from './components/NavBar'
import Grid from './components/Grid'
import Footer from './components/Footer'
//import Popup from './components/Popup'
//import Overall from './components/Overall'
import Popular from './components/Popular'
import SummaryChart from './components/SummaryChart'
import LineChart1 from './components/LineChart1'
import LineChartRemain from './components/LineChartRemain'
//import ApexCharts from 'apexcharts'
import { useState, useEffect } from 'react'
import './App.css';


const theme = createTheme({
  palette: {
    primary: {
      main:"#00865a",
    },
    secondary: {
      main:"#c7d8ed",
    },
  },
  typography: {
    fontFamily: [
      'Roboto'
    ],
    h4: {
      fontWeight: 600,
      fontSize: 28,
      lineHeight: '2rem',
      },
    h5: {
      fontWeight: 100,
      lineHeight: '2rem',
    },
  },
});

const styles = makeStyles({
  wrapper: {
    width: "65%",
    margin: "auto",
    textAlign: "center"
  },
  bigSpace: {
    marginTop: "5rem",
    flex: '1',
    width: '80%',
    //overflow: 'auto'
  },
  specialChungus: {
    marginTop: "5rem"
  },
  littleSpace:{
    marginTop: "2.5rem",
  },
  grid:{
    display: "flex", 
    justifyContent: "center",
    alignItems: "center",
    flexWrap: "wrap", 
  },
  graph:{
    display: 'flex',
    flexDirection: 'column',
    alignItems: 'center'
  },
  chartWrapper:{
    width: '100%',
    height: '100%'
  }
})

function App() {
  const classes = styles(); 
 // const [buttonPopup, setButtonPopup] = useState(false);  //for settings button. currently not working
 
  //begin chart code (below footer)
  /*
    data = [
      {flavor: "Blue", value:100},   
      {flavor: "Lemon", value:200},

    ];
    let values=[];
    let flavors=[]'
    
    data.forEach ((row)={
      flavors.push(row.flavor);
      values.push(row.value);
    });
    setValues(values);
    setFlavors(flavors);

  */

  //Chart 1 Options
  

  return (
    <div className="App">
     
     
      <ThemeProvider theme={theme}>
        <NavBar/>
        <div className={classes.wrapper}>
          <Typography variant="h4" className={classes.specialChungus} color="primary">
             Stock your restaurant with hyper efficiency
          </Typography>
          <Typography variant="h5" className={classes.littleSpace} color="primary">
            Below is the data for product consumption at your restaurant: Ted's BBQ. These rates are meant to help you make better informed decisions on stocking goods.
          </Typography>
        </div>
        <div className={classes.bigSpace}/>
        <h3>Dispenser Machine ID: #10</h3>

  <div className={classes.graph}>

      <div className={classes.bigSpace}>
          <div className={classes.chartWrapper}><SummaryChart/></div>
      </div>
      <div className={classes.bigSpace}>
      <div className={classes.chartWrapper}><LineChart1/></div>
     </div>
     <div className={classes.bigSpace}>
     <div className={classes.chartWrapper}><LineChartRemain/></div>
     </div>

  </div>
 
        <br/><br/><br/><br/><br/><br/><br/><br/><br/>
        <Footer/>
        <div className="container">
      

    </div>


      </ThemeProvider>
    </div>
  );
}

export default App;