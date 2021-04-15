import React, { Component } from 'react';

class Car extends Component { 
    render() {
        const handleClick = _ =>{
            this.props.handleVoteChange(this.props.id);
        }
        return (
            <tr>
                <td>{this.props.brand}</td>
                <td>{this.props.style}</td>
                <td>{this.props.votes}</td>
                <td>{this.props.stars}</td>
                <td>{<button onClick={handleClick}>Vote</button>}</td>
            </tr>         
        );
    }
};

export default Car;