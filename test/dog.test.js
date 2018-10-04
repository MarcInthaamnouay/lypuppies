const { expect } = require('chai');
const lib = require('../build/Release/lypuppies');

describe('Creation of a dog', () => {
  it('expect dog to have the property name: 明媚', () => {
    const dog = lib.GenerateUniquePuppy('明媚', 'chihuahua');
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

  it('expect dog to be a chihuahua if type is not pass', () => {
    const dog = lib.GenerateUniquePuppy('miaomiao');
    expect(dog).to.deep.include({ type: 'chihuahua' });
  });

  it('expect generate unique puppy to throw when no name is pass', () => {
    expect(() => lib.GenerateUniquePuppy()).to.throw('Unable to parse dog name. Check name param');
  });
});

describe('Barking of a dog', () => {
  it('expect dog to bark', () => {
    const dog = lib.GenerateUniquePuppy('明媚', 'chihuahua');
    expect(() => lib.PuppyBark(dog)).to.not.throw();
  });

  it('expect dog to not bark when name is not present', () => {
    const dog = lib.GenerateUniquePuppy('meimei', 'dogWolf');
    delete dog.name;

    expect(() => lib.PuppyBark(dog)).to.not.throw();
  });
});

describe('Get dog age', () => {
  it('expect to get dog age of type chihuahua', () => {
    const dog = lib.GenerateUniquePuppy('mitsuha', 'chihuahua');
    const age = lib.GetPuppyExpectedLife(dog);

    expect(age).to.be.equal(15);
  });

  it('expect to get dog age of type dogWolf', () => {
    const dog = lib.GenerateUniquePuppy('taki', 'dogWolf');
    const age = lib.GetPuppyExpectedLife(dog);

    expect(age).to.be.equal(14);
  });

  it('expect to get default dog age from an unknown type', () => {
    const dog = lib.GenerateUniquePuppy('tako', 'dogWolf');
    dog.type = 'shetlandSheepdog';
    const age = lib.GetPuppyExpectedLife(dog);

    expect(age).to.be.equal(14);
  });
});
