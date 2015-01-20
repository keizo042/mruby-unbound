mruby-unbound
====


## Descriotion
libunbound mruby client.
unbound is DNS cache Server

## sample

c = Unbound.new  
c.resolv "forum.mruby.org"  
=> "176.34.60.232"  

## Requirement

unbound & libunbound

## Install

on your build_config.rb
MRuby:Build.new do |conf|  
conf.gem :github => "KeizoBookman/mruby-unbound"  
end  
  
## LICENSE

same mruby LICENSE. MITL

## AUTHOR

[keizo](https://github.com/KeizoBookman]


## Contact me
twitter : @keizo_bookman  
mail: keizo.bookman at gmail.com  
