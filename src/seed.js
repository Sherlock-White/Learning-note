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
        view:true,
      },
      {
        id: 2,
        brand:'BENZ',
        style:'Sprinter',
        votes: generateVoteCount(),
        view:true,
      },
      {
        id: 3,
        brand:'Ford',
        style:'focus',
        votes: generateVoteCount(),
        view:true,
      },
      {
        id: 4,
        brand:'Chevrolet',
        style:'VengaSoul',
        votes: generateVoteCount(),
        view:true,
      },
    ];
  
    return { cars: cars };
  }());
  