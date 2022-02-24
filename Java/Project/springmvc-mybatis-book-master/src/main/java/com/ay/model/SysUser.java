package com.ay.model;

import java.io.Serializable;

/**
 * 员工表
 * Created by Ay on 2020/3/22.
 */
public class SysUser implements Serializable {
    //主键
    private Integer id;
    //用户名
    private String name;
    //工号
    private String no;
    //职位
    private String position;
    //离职原因
    private String reason;
    //状态，0：删除 1：在职  2：离职
    private String status;

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getNo() {
        return no;
    }

    public void setNo(String no) {
        this.no = no;
    }

    public String getPosition() {
        return position;
    }

    public void setPosition(String position) {
        this.position = position;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getReason() {
        return reason;
    }

    public void setReason(String reason) {
        this.reason = reason;
    }
}
