window.Seed = (function () {
    function generateVoteCount() {
      return Math.floor((Math.random() * 50) + 15);
    }
    const cars = [
      {
        id: 1,
        brand:'TOYOTA',
        style:'ZRE120',
        votes: generateVoteCount(),
      },
      {
        id: 2,
        brand:'BENZ',
        style:'Sprinter',
        votes: generateVoteCount(),
      },
      {
        id: 3,
        brand:'Ford',
        style:'focus',
        votes: generateVoteCount(),
      },
      {
        id: 4,
        brand:'Chevrolet',
        style:'VengaSoul',
        votes: generateVoteCount(),
      },
    ];
  
    return { cars: cars };
  }());
  