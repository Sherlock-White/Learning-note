import React, { Component } from 'react';
import './CarList.css'

import Car from './Car';
import Filter from './Filter';
import "./seed"
class CarList extends Component {
    state = {
        cars: [],
        sortTag:'',/*brand, style,votes or stars */
        sortWay:'',/*ascend or descend */
        filterCondition:false,
    };
    calculateStar(voteNum) {
        let num = Number(voteNum);
        if(num >= 50){
          return 5;
        }else{
          return Math.floor(num/10);
        }
    }
    sortByTag(x,y,sortWay,sortTag){
        //console.log('init'+ sortWay);
        let a,b;
        if(sortTag ==='votes'||sortTag ==='stars'){
            a = Number(x.votes);
            b = Number(y.votes);
        }else if(sortTag ==='brand'){
            a = x.brand;
            b = y.brand;
        }else{
            a = x.style;
            b = y.style;
        }

        if(a === b){
            return 0;
        }else{
            if(sortWay === 'descend'){
                if(b > a){
                    return 1;
                }else{
                    return -1;
                }
            }else{
                if(a > b){
                    return 1;
                }else{
                    return -1;
                }
            }
        }
    }
    changeSortWay(carsCopy,buttonType){
        //console.log(state.sortWay);
        let nextSortWay = buttonType;
        carsCopy.sort((x,y)=>{
            return (this.sortByTag(x,y,nextSortWay,this.state.sortTag));
        });
        this.setState({
            cars:carsCopy,
            sortWay:nextSortWay,
        });
    }
    changeSortTag(carsCopy,newSortTag){
        carsCopy.sort((x,y)=>{
            return (this.sortByTag(x,y,this.state.sortWay,newSortTag));
        });
        this.setState({
            cars:carsCopy,
            sortTag:newSortTag,
        });
    }
    changeFilterCondition(filterCon){
        let condition = (filterCon === false)?true:false;
        this.setState({
            filterCondition:condition,
        });
    }
    changeViewCondition(carsCopy,selectedValue,selectedTag){
        let mycars = carsCopy;
        if(selectedValue === 'all'){
            mycars.map((car)=>{
                car.view = true;
            });
        }else{
            mycars.map((car)=>{
                car.view = false;
                switch(selectedTag){
                    case "selectBrand":
                        if(car.brand === selectedValue){
                            car.view = true;
                        }
                        break;
                    case "selectStyle":
                        if(car.style === selectedValue){
                            car.view = true;
                        }
                        break;
                    case "selectVotes":
                        if(car.votes === selectedValue){
                            car.view = true;
                        }
                        break;
                    case "selectStars":
                        if(car.stars === selectedValue){
                            car.view = true;
                        }
                        break;
                }
            });
        }
        console.log(mycars);
        /*this.setState({
            cars:mycars,
        });*/
    }
    //组件初始化结束后框架会调用这个函数
    //This function is called by the framework after the initialization of the component is complete.
    componentDidMount() {
        const cars = window.Seed.cars;
        cars.sort((x,y)=>{
            return (this.sortByTag(x,y,'descend','votes'));
        });
        this.setState({
            cars:cars,
            sortTag:'votes',
            sortWay:'descend',
            filterCondition:false,
        });
    }

    render() {
        const mycars = this.state.cars;
        const tableTitle = (
            <tr>
                <th><button onClick={()=>{this.changeSortTag(this.state.cars,'brand')}}>Brand</button></th>
                <th><button onClick={()=>{this.changeSortTag(this.state.cars,'style')}}>Style</button></th>
                <th><button onClick={()=>{this.changeSortTag(this.state.cars,'votes')}}>Votes</button></th>
                <th><button onClick={()=>{this.changeSortTag(this.state.cars,'stars')}}>Stars</button></th>
                <th>{'Buttons'}</th>
            </tr>
        );
        const tableTitleWithFilter = (
            <Filter 
                key={'filter'}
                cars={mycars}
                handleStarCal={this.calculateStar}
                handleSelect={this.changeViewCondition}
            />
        );
        const changeVote = id =>{
            this.setState(mycars.map(car=>(
                (car.id === id) ?({
                    ...car,
                    votes:car.votes++, 
                }):car
                )));
            mycars.sort((x,y)=>{
                return (this.sortByTag(x,y,this.state.sortWay,this.state.sortTag));
            });
            this.setState({
                cars:mycars,
            });
        }
        const carComponents = mycars.map((car) => (
            <Car
                key={'car-' + car.id}
                id={car.id}
                brand={car.brand}
                style={car.style}
                votes={car.votes}
                stars={this.calculateStar(car.votes)}
                view = {car.view}
                handleVoteChange={changeVote}
            />
        ));
        const sortWayButtons = (
        <ul id = 'sort'>
            {'Choose a sort way:'}
            <button onClick={()=>{this.changeSortWay(this.state.cars,'ascend');}}>
                ascend
            </button>
            <button onClick={()=>{this.changeSortWay(this.state.cars,'descend')}}>
                descend
            </button>
        </ul>
        );
        ////////////////////////////////////////////////////
        const search = (
            <div>
                <form method="get">
                    <label>Search here: 
                    <input type = "search"></input></label>
                    <button>search</button>
                </form>
            </div>
        );
        const filter = (
            <div>
                {'Click to filter: '}
                <button onClick={()=>{this.changeFilterCondition(this.state.filterCondition)}}>filter</button>
            </div>
        );
        if(this.state.filterCondition){
            return (
                <div>
                    <div>
                        <table>
                            <thead>
                            {tableTitle}
                            {tableTitleWithFilter}
                            </thead>
                            <tbody>
                                {carComponents}
                            </tbody>
                        </table>
                        <div>
                            {sortWayButtons}
                            <br></br>
                            {search}
                            <br></br>
                            {filter}
                        </div>
                    </div>
                </div>);
        }else{
            return (
                <div>
                    <div>
                        <table>
                            <thead>{tableTitle}</thead>
                            <tbody>{carComponents}</tbody>
                        </table>
                        <div>
                            {sortWayButtons}
                            <br></br>
                            {search}
                            <br></br>
                            {filter}
                        </div>
                    </div>
                </div>);
        }
    }
};

export default CarList;