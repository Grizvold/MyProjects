package com.example.demo;

import java.util.Map;

import javax.servlet.http.HttpServletResponse;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.servlet.support.ServletUriComponentsBuilder;

@SpringBootApplication
@RestController
public class DemoApplication {

	public static void main(String[] args) {
		SpringApplication.run(DemoApplication.class, args);
	}
	
	@GetMapping("/hello")
	public String helloTest(@RequestParam(value = "name", defaultValue = "world") String name) {
		return String.format("Hello %s!", name);
	}
	
//	@PostMapping(
//	value = "/createPerson", consumes = "application/json", produces = "application/json")
//	public Person createPerson(@RequestBody Person person) {
//	    return personService.saveUpdatePerson(person);
//	}
//	 
//	@PostMapping(
//	  value = "/updatePerson", consumes = "application/json", produces = "application/json")
//	public Person updatePerson(@RequestBody Person person, HttpServletResponse response) {
//	    response.setHeader("Location", ServletUriComponentsBuilder.fromCurrentContextPath()
//	      .path("/findPerson/" + person.getId()).toUriString());
//	     
//	    return personService.saveUpdatePerson(person);
//	}
//	
//	@PostMapping(
//			  value = "/updatePerson", consumes = "application/json", produces = "application/json")
//			public Person updatePerson(@RequestBody Map<String, Object> person, HttpServletResponse response) {
//			    response.setHeader("Location", ServletUriComponentsBuilder.fromCurrentContextPath()
//			      .path("/findPerson/" + person.get("")).toUriString());
//			     
//			    return personService.saveUpdatePerson(person);
//			}
			
}
