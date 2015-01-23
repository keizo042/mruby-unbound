MRuby::Gem::Specification.new('mruby-unbound') do |spec|
    spec.license = 'MIT'
    spec.authors = 'keizo'
    spec.cc.flags = '-lunbound'
    spec.linker.libraries << "unbound"

end

