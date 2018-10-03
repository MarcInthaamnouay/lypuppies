const { expect } = require('chai');
const lib = require('../build/Release/lypuppies');

describe('Creation of a dog', () => {
  it('expect dog to have the property name: 明媚', () => {
    const dog = lib.GenerateUniquePuppy('明媚', 'chihuhua');
    expect(dog).to.deep.include({ name: '明媚' });
  });

  it('expect dog to be of a type chihuahua', () => {
    const dog = lib.GenerateUniquePuppy('meimei', 'chihuahua');
    expect(dog).to.deep.include({ type: 'chihuahua' });
  });

  it('expect dog to be of a type wolfdog', () => {
    const dog = lib.GenerateUniquePuppy('mia', 'dogWolf');
    expect(dog).to.deep.include({ type: 'dogWolf' });
  });
});
