import React, { Component } from 'react';

class Filter extends Component {
    render() {
        const handleStar = (car) =>{
            return this.props.handleStarCal(car.votes);
        }
        const handleClick = _ =>{
            //return this.props.handleSelect()
            //console.log('aaaaaaaa');
        }
        const handleSelect = ()=>{

        }
        
        return(
            <tr>
                <th><select id = "selectBrand" onChange = {()=>{
                    let selectedValue = document.getElementById("selectBrand").value;
                    this.props.handleSelect(this.props.cars,selectedValue,"selectBrand");
                }}>
                    <option value = 'all'>all</option>
                    {this.props.cars.map((car) => (
                        <option value = {car.brand} id = {car.id}>{car.brand}</option>
                    ))}
                    </select></th>
                <th><select id = "selectStyle" onChange = {()=>{
                    let selectedValue = document.getElementById("selectStyle").value;
                    this.props.handleSelect(this.props.cars,selectedValue,"selectStyle");
                }}>
                    <option value = 'all'>all</option>
                    {this.props.cars.map((car) => (
                        <option value = {car.style} >{car.style}</option>
                    ))}
                    </select></th>
                <th><select id = "selectVotes" onChange = {()=>{
                    let selectedValue = document.getElementById("selectVotes").value;
                    this.props.handleSelect(this.props.cars,selectedValue,"selectVotes");
                }}>
                    <option value = 'all'>all</option>
                    {this.props.cars.map((car) => (
                        <option value = {car.votes} >{car.votes}</option>
                    ))}
                    </select></th>
                <th><select id = "selectStars" onChange = {()=>{
                    let selectedValue = document.getElementById("selectStars").value;
                    this.props.handleSelect(this.props.cars,selectedValue,"selectStars");
                }}>
                    <option value = 'all'>all</option>
                    {this.props.cars.map((car) => (
                        <option value = {handleStar(car)} >{handleStar(car)}</option>
                    ))}
                    </select></th>
                <th><button onClick = {handleClick}>Yes</button></th>
            </tr>
        );
    }
};

export default Filter;