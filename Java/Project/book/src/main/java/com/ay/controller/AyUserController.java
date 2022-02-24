package com.ay.controller;

import com.ay.model.AyUser;
import com.ay.service.AyUserService;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.springframework.http.converter.json.Jackson2ObjectMapperBuilder;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import java.util.List;

/**
 * 用户控制层
 *
 * @author Ay
 * @date 2018/04/02
 */
@Controller
@RequestMapping("/user")
public class AyUserController {
    @Resource
    private AyUserService ayUserService;

    @GetMapping("/findAll")
    public String findAll(Model model){
        List<AyUser> ayUserList = ayUserService.findAll();
        for(AyUser ayUser : ayUserList){
            System.out.println("id: " + ayUser.getId());
            System.out.println("name: " + ayUser.getName());
        }


        return "hello";
    }

    @PostMapping("/findAll")
    @ResponseBody
    public String find(@RequestBody String req, Model model) throws JsonProcessingException {
        System.out.println(req);
        ObjectMapper mapper = new ObjectMapper();
        AyUser user = new AyUser(){
            {
                setId(1);setName("司展宇");setPassword("123");
            }
        };
        String str = mapper.writeValueAsString(user);
        return str;
    }



}
